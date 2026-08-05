//
// Created by Spaced Viking on 24.06.2026
//

#include "RuleNodeManager.h"
#include "RuleNode.h"
#include "utils.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>
#include <RuleNodeTreeModel.h>
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <qcontainerfwd.h>
#include <qobject.h>

namespace Rules {
QVector<Rule> ruleNodes; // holds ptrs to all nodes displayed in the list view
QMap<QString, Rule>
    rules; // holds ptrs to all nodes in memory (for quick access)

// TODO make RuleNodeManager non static
std::shared_ptr<RuleNodeChangesEventEmitter> ermitter; // emits events

/**
 * @brief One Rule to rule them all, One Rule to find them.
 *        One Rule to bring them all and in the memory bind them.
 *        In the Land of Code where the Shadows lie.
 */
std::shared_ptr<RuleNode> root;
Rule activeChapter; // the active chapter

bool RuleNodeManager::ChangeName(Rule rule, QString newName) {
  if (rules.contains(newName)) { // check, if rule valid
    return false;
  }

  rules.remove(rule->name()); // if valid, remove old name
  rules[newName] = rule;      // add new name
  rule->_setname(newName);    // set the new name

  ermitter->emit ruleNameChanged(rule); // fire rule name changed event
  return true;
}

Rule RuleNodeManager::GetRule(QString ruleName) {
  if (rules.contains(ruleName)) {
    return rules[ruleName]; // return rule if exists
  }
  return nullptr;
}

Rule RuleNodeManager::GetRule(int id) {
  if (id >= ruleNodes.size() || id < 0) {
    return nullptr;
  }
  return ruleNodes[id]; // return rule if exists
}

RuleNodeChangesEventEmitter *RuleNodeManager::GetSignalErmitter() {
  return ermitter.get(); // return signal emitter as raw ptr
}

// return root node
Rule RuleNodeManager::GetRoot() { return root.get(); }

// check if name is taken
bool RuleNodeManager::NameTaken(QString name) { return rules.contains(name); }

/**
 * @brief Creates a rule
 *
 * @param name the name
 * @param desc the description
 * @param parent the parent (if nullptr == Root)
 * @param useParentTemplate if should use template
 * @return Rule
 */
Rule RuleNodeManager::CreateRule(QString name, QString desc, Rule parent,
                                 bool useParentTemplate, bool chapter) {

  if (NameTaken(name)) { // name already taken
    return nullptr;
  }

  if (!parent && name != "Root") { // set parent to root if not specified
    parent = root.get();
  }

  Rule rule = new RuleNode(parent, name,
                           desc); // create the rule

  if (!rule) {
    return nullptr; // something went horribly wrong
  }

  rules[name] = rule; // map the rule to its name

  if (name !=
      "Root") { // only if not root add to list // TODO change list index gen

    if (parent == activeChapter) {
      ruleNodes.push_back(
          rule); // when parent is active chapter, append to the end of the list
    } else if (ruleNodes.contains(parent)) {
      ruleNodes.insert(
          ruleNodes.indexOf(parent) + 1,
          rule); // otherwise append to the end of the parent's "list"
    }
  }

  rule->setchapter(chapter); // pass the chapter arg to the rule
  ermitter->emit ruleChildAdded(parent, rule); // emit child added signal
  return rules[name];                          // return the created Rule
}

Rule RuleNodeManager::LoadRule(
    QJsonObject obj) { // load a rule from json object

  if (obj.isEmpty()) { // empty json
    return nullptr;
  }

  QString name = obj["name"].toString();               // rule name
  QString description = obj["description"].toString(); // rule description
  QString parent = obj["parent"].toString();           // parent rule name
  bool chapter = obj["chapter"].toBool();              // is rule a chapter
  return CreateRule(name, description, GetRule(parent), false,
                    chapter); // create rule
}

/**
 * @brief recursively add the children of the current chapter to the listview
 * list
 *
 * @param parent
 */
void AddChapterChildren(Rule parent) {
  ruleNodes.push_back(parent);
  auto &children = parent->children();

  for (QObject *obj : children) {
    AddChapterChildren((Rule)obj); // recursively add children
  }
}

void RuleNodeManager::SetChapter(Rule newChapter) {
  if (!newChapter) { // when invalid, default to root
    newChapter = root.get();
  }

  while (!newChapter->chapter() &&
         newChapter->parent()) { // find the next chapter in parents
    newChapter = (Rule)newChapter->parent();
  }

  if (newChapter == activeChapter) {
    return; // chapter already active
  }

  int oldRuleCount = ruleNodes.size(); // save the current chapter rule count
  Rule oldChapter = activeChapter;     // save the current chapter

  ruleNodes.clear();          // clear the rule nodes
  activeChapter = newChapter; // set the new chapter

  const QObjectList &children = newChapter->children();

  // recursively add the children of the current chapter to  the listview list
  if (activeChapter == root.get()) {
    for (QObject *obj : children) {
      AddChapterChildren((Rule)obj);
    }
  } else {
    AddChapterChildren(activeChapter);
  }

  ermitter->emit ruleChapterChanged(
      oldChapter, newChapter, oldRuleCount); // emit the chapter changed signal
}

void RuleNodeManager::LoadFromFile(QString path) {
  if (path.isEmpty()) {
    path = Utils::GetRelativePath("/Saves/default.json");
  }
  QJsonDocument doc =
      QJsonDocument::fromJson(Utils::ReadFile(path)); // read the json file

  if (doc.isNull() || doc.isEmpty()) {
    return; // json invalid
  }

  QJsonArray rules = doc["rules"].toArray();
  for (auto it : rules) {
    LoadRule(it.toObject()); // load rules recursively
  }
}

void GetChildrenSave(Rule parent, QJsonArray &array) {
  array.append(parent->Save());
  for (auto child : parent->children()) {
    GetChildrenSave((Rule)child, array); // save children recursively
  }
}

void RuleNodeManager::SaveToFile(QString path) {
  if (path.isEmpty()) {
    path = Utils::GetRelativePath("/Saves/default.json");
  }
  return RuleNodeManager::SaveToFile(path);
  QJsonArray array;
  for (auto child : GetRoot()->children()) {
    GetChildrenSave((Rule)child, array); // save children recursively
  }
  QJsonObject obj;
  obj["rules"] = array;

  QJsonDocument doc(obj);
  Utils::WriteFile(path, doc.toJson()); // write json file
}

// return the rule count for the listview
int RuleNodeManager::GetRuleCount() { return (ruleNodes.size()); }

void RuleNodeManager::Init(QJsonObject *save) {
  ermitter =
      std::make_shared<RuleNodeChangesEventEmitter>(); // init event emitter
  root = std::make_shared<RuleNode>(
      CreateRule("Root", "The root node of the rule tree.", nullptr, false,
                 true));  // create root
  root->setchapter(true); // make the root a chapter
  SetChapter();           // set the root as chapter
}

int RuleNodeManager::GetRuleIndex(QString ruleName) {
  return ruleNodes.indexOf(GetRule(ruleName)); // return the index of the rule
}

bool RuleNodeManager::ChangeParent(Rule rule, Rule newParent) {
  if (rule == root.get()) {
    return false; // root can not be reparented
  }

  // validate input
  if (!rule) {
    return false;
  }
  if (!newParent) {
    return false;
  }

  Rule oldParent = (Rule)rule->parent();
  int oldIndex = rule->IndexInParent();
  rule->setParent(oldParent);
  SetChapter(activeChapter);
  ermitter->emit ruleParentChanged(rule, oldParent, oldIndex, newParent);
  return true;
}

QStringList RuleNodeManager::GetRulesNames() {
  QStringList rulesNames;
  for (auto rule : rules) {
    rulesNames.push_back(rule->name());
  }
  return rulesNames;
}
} // namespace Rules