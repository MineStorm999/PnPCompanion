//
// Created by Spaced Viking on 24.06.2026
//

#include "RuleNodeManager.h"
#include "RuleNode.h"
#include <QVector>
#include <RuleNodeTreeModel.h>
#include <memory>

namespace Rules {
QVector<Rule> ruleNodes; // TODO add node hierarchy
QMap<QString, Rule> rules;

QVector<RuleNodeTreeModel *> childrenChangedNotifySubs;

std::shared_ptr<RuleNode> root;

bool RuleNodeManager::ChangeName(Rule rule, QString newName) {
  if (rules.contains(newName)) {
    return false;
  }
  rules.remove(rule->name());
  rules[newName] = rule;
  rule->_setname(newName);
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

void AddChildChangedNotify(RuleNodeTreeModel *notified) {
  childrenChangedNotifySubs.push_back(notified);
}

Rule RuleNodeManager::GetRoot() { return root.get(); }

bool RuleNodeManager::NameTaken(QString name) { return rules.contains(name); }

Rule RuleNodeManager::CreateRule(QString name, QString desc, Rule parent,
                                 bool useParentTemplate) {
  if (NameTaken(name)) {
    return nullptr;
  }
  if (!parent) {
    parent = root.get(); // has to have a parent
  }
  Rule rule =
      new RuleNode(parent, name,
                   desc); // std::make_shared<RuleNode>(parent, name, desc);
  if (!rule) {
    return nullptr;
  }
  rules[name] = rule;
  if (name != "Root") {
    if (parent && ruleNodes.contains(parent)) {
      ruleNodes.insert(ruleNodes.indexOf(parent) + 1, rule);
    } else {
      ruleNodes.push_back(rule); // TODO add node hierarchy
    }
  }
  for (RuleNodeTreeModel *sub : childrenChangedNotifySubs) {
    sub->ChildrenChanged(parent);
  }
  return rules[name];
}

int RuleNodeManager::GetRuleCount() { return (ruleNodes.size()); }

void RuleNodeManager::Init(QJsonObject *save) {
  root = std::make_shared<RuleNode>(
      CreateRule("Root", "The root node of the rule tree.", nullptr, false));
}

int RuleNodeManager::GetRuleIndex(QString ruleName) {
  return ruleNodes.indexOf(GetRule(ruleName));
}

} // namespace Rules