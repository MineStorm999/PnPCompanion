//
// Created by Spaced Viking on 24.06.2026
//

#include "RuleNodeManager.h"
#include "RuleNode.h"
#include <QVector>
#include <memory>

namespace Rules {
QVector<Rule> ruleNodes; // TODO add node hierarchy
QMap<QString, Rule> rules;

Rule root;
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

Rule RuleNodeManager::GetRule(int id) { // TODO add node hierarchy
  if (id >= ruleNodes.size() || id < 0) {
    return nullptr;
  }
  return ruleNodes[id];
}

bool RuleNodeManager::NameTaken(QString name) { return rules.contains(name); }

Rule RuleNodeManager::CreateRule(QString name, QString desc, Rule parent,
                                 bool useParentTemplate) {
  if (NameTaken(name)) {
    return nullptr;
  }
  if (!parent) {
    parent = root; // has to have a parent
  }
  Rule rule = std::make_shared<RuleNode>(parent.get(), name, desc);
  if (!rule) {
    return nullptr;
  }
  rules[name] = rule;
  if (name != "Root") {
    ruleNodes.push_back(rule); // TODO add node hierarchy
  }
  return rules[name];
}

int RuleNodeManager::GetRuleCount() { return (ruleNodes.size()); }

void RuleNodeManager::Init(QJsonObject *save) {
  root = CreateRule("Root", "The root node of the rule tree.", nullptr, false);
}

} // namespace Rules