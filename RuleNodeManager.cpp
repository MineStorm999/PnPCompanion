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
#include <memory>
#include <qjsonarray.h>
#include <qjsonobject.h>

namespace Rules {
QVector<Rule> ruleNodes; // TODO add node hierarchy
QMap<QString, Rule> rules;

QVector<RuleNodeTreeModel *> childrenChangedNotifySubs;

std::shared_ptr<RuleNodeChangesEventEmitter> ermitter;

std::shared_ptr<RuleNode> root;

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
    return rules[ruleName];
  }
  return nullptr;
}

Rule RuleNodeManager::GetRule(int id) { // TODO add node hierarchy
  if (id >= ruleNodes.size() || id < 0) {
    return nullptr;
  }
  return ruleNodes[id];
}

RuleNodeChangesEventEmitter *RuleNodeManager::GetSignalErmitter() {
  return ermitter.get();
}

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
                                 bool useParentTemplate) {
  if (NameTaken(name)) { // name already taken
    return nullptr;
  }

  if (!parent) { // set parent to root if not specified
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
    if (parent && ruleNodes.contains(parent)) {
      ruleNodes.insert(ruleNodes.indexOf(parent) + 1, rule);
    } else {
      ruleNodes.push_back(rule); // TODO add node hierarchy
    }
  }

  ermitter->emit ruleChildAdded(parent, rule); // emit child added signal
  return rules[name];
}

Rule RuleNodeManager::LoadRule(QJsonObject obj) {
  if (obj.isEmpty()) {
    return nullptr;
  }
  QString name = obj["name"].toString();
  QString description = obj["description"].toString();
  QString parent = obj["parent"].toString();
  return CreateRule(name, description, GetRule(parent), false);
}

void RuleNodeManager::LoadFromFile(QString path) {
  QJsonDocument doc = QJsonDocument::fromJson(Utils::ReadFile(path));
  if (doc.isNull() || doc.isEmpty()) {
    return;
  }
  QJsonArray rules = doc["rules"].toArray();
  for (auto it : rules) {
    LoadRule(it.toObject());
  }
}

void GetChildrenSave(Rule parent, QJsonArray &array) {
  array.append(parent->Save());
  for (auto child : parent->children()) {
    GetChildrenSave((Rule)child, array);
  }
}

void RuleNodeManager::SaveToFile(QString path) {
  QJsonArray array;
  for (auto child : GetRoot()->children()) {
    GetChildrenSave((Rule)child, array);
  }
  QJsonObject obj;
  obj["rules"] = array;

  QJsonDocument doc(obj);
  Utils::WriteFile(path, doc.toJson());
}

int RuleNodeManager::GetRuleCount() { return (ruleNodes.size()); }

void RuleNodeManager::Init(QJsonObject *save) {
  ermitter = std::make_shared<RuleNodeChangesEventEmitter>();
  root = std::make_shared<RuleNode>(
      CreateRule("Root", "The root node of the rule tree.", nullptr, false));
}

int RuleNodeManager::GetRuleIndex(QString ruleName) {
  return ruleNodes.indexOf(GetRule(ruleName));
}

} // namespace Rules