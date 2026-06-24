//
// Created by Spaced Viking on 24.06.2026
//

#include "RuleNodeManager.h"
#include "RuleNode.h"
#include <QVector>
#include <memory>

namespace Rules {
QVector<Rule> ruleNodes;
QMap<QString, Rule> rules;

void RuleNodeManager::ChangeName(std::shared_ptr<Rules::RuleNode> rule,
                                 QString newName) {
  if (rules.contains(newName)) {
    return;
  }
  rules.remove(rule->name());
  rule->_setname(newName);
  rules[newName] = rule;
}

Rule RuleNodeManager::GetRule(QString ruleName) {
  if (rules.contains(ruleName)) {
    return rules[ruleName];
  }
  return nullptr;
}

bool RuleNodeManager::NameTaken(QString name) { return rules.contains(name); }

Rule RuleNodeManager::CreateRule(QString name, QString desc,
                                 QString parentString, bool useParentTemplate) {
  if (NameTaken(name)) {
    return nullptr;
  }
  Rule parent = nullptr;
  if (rules.contains(parentString)) {
    parent = rules[parentString];
  }
  return CreateRule(name, desc, parent, useParentTemplate);
}

Rule RuleNodeManager::CreateRule(QString name, QString desc, Rule parent,
                                 bool useParentTemplate) {
  if (NameTaken(name)) {
    return nullptr;
  }
  Rule rule = std::make_shared<RuleNode>(parent.get(), name, desc);
  if (!rule) {
    return nullptr;
  }
  rules[name] = rule;
  return rules[name];
}

} // namespace Rules