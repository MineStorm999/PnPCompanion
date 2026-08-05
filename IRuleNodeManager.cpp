//
// Created by Spaced Viking on 05.08.2026
//

#include "IRuleNodeManager.h"
#include "RuleNodeManager.h"
#include <QJsonObject>

namespace Rules {
IRuleNodeManager::IRuleNodeManager(QObject *parent) : QObject{parent} {
  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleNameChanged, this,
          &IRuleNodeManager::_ruleNameChanged);

  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleParentChanged, this,
          &IRuleNodeManager::_ruleParentChanged);

  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleDataChanged, this,
          &IRuleNodeManager::_ruleDataChanged);

  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleChildAdded, this,
          &IRuleNodeManager::_ruleChildAdded);

  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleChapterChanged, this,
          &IRuleNodeManager::_ruleChapterChanged);
};

Rule IRuleNodeManager::loadRule(QJsonObject obj) {
  return RuleNodeManager::LoadRule(obj);
};

bool IRuleNodeManager::changeName(Rule rule, QString newName) {
  return RuleNodeManager::ChangeName(rule, newName);
};

bool IRuleNodeManager::changeParent(Rule rule, Rule newParent) {
  return RuleNodeManager::ChangeParent(rule, newParent);
}

RuleNode *IRuleNodeManager::getRoot() { return RuleNodeManager::GetRoot(); }

RuleNode *IRuleNodeManager::getRule(QString ruleName) {
  return RuleNodeManager::GetRule(ruleName);
};

Rule IRuleNodeManager::getRule(int id) { return RuleNodeManager::GetRule(id); };

int IRuleNodeManager::getRuleIndex(QString ruleName) {
  return RuleNodeManager::GetRuleIndex(ruleName);
}
QStringList IRuleNodeManager::getRulesNames() {
  return RuleNodeManager::GetRulesNames();
};
;

int IRuleNodeManager::getRuleCount() {
  return RuleNodeManager::GetRuleCount();
};

Rule IRuleNodeManager::createRule(QString name, QString desc, Rule parent,
                                  bool useParentTemplate, bool chapter) {
  return RuleNodeManager::CreateRule(name, desc, parent, useParentTemplate,
                                     chapter);
};

void IRuleNodeManager::setChapter(Rule newChapter) {
  return RuleNodeManager::SetChapter(newChapter);
};

void IRuleNodeManager::loadFromFile(QString path) {
  return RuleNodeManager::LoadFromFile(path);
}

void IRuleNodeManager::saveToFile(QString path) {
  return RuleNodeManager::SaveToFile(path);
}

bool IRuleNodeManager::nameTaken(QString name) {
  return RuleNodeManager::NameTaken(name);
}

// INTERNAL
void IRuleNodeManager::_ruleNameChanged(RuleNode *rule) {
  emit ruleNameChanged(rule);
};
void IRuleNodeManager::_ruleParentChanged(RuleNode *rule, RuleNode *oldParent,
                                          int oldIndex, RuleNode *newParent) {
  emit ruleParentChanged(rule, oldParent, oldIndex, newParent);
}
void IRuleNodeManager::_ruleDataChanged(RuleNode *rule) {
  emit ruleDataChanged(rule);
};
;
void IRuleNodeManager::_ruleChildAdded(RuleNode *parent, RuleNode *child) {
  emit ruleChildAdded(parent, child);
}
void IRuleNodeManager::_ruleChapterChanged(RuleNode *oldChapter,
                                           RuleNode *newChapter,
                                           int oldRuleCount) {
  emit ruleChapterChanged(oldChapter, newChapter, oldRuleCount);
};
;

} // namespace Rules