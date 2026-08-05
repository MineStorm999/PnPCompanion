//
// Created by Spaced Viking on 05.08.2026
//

#pragma once
#include "RuleNodeManager.h"
#include <QObject>
#include <qqmlintegration.h>

namespace Rules {
class IRuleNodeManager : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit IRuleNodeManager(QObject *parent = nullptr);

signals:
  void ruleNameChanged(Rule rule);
  void ruleParentChanged(Rule rule, Rule oldParent, int oldIndex,
                         Rule newParent);
  void ruleDataChanged(Rule rule); // TODO implement ruleDataChanged
  void ruleChildAdded(Rule parent, Rule child);
  void ruleChapterChanged(Rule oldChapter, Rule newChapter,
                          int oldRuleCount); // TODO implement ruleChapters

public slots:
  bool ChangeName(Rule rule, QString newName) {
    return RuleNodeManager::ChangeName(rule, newName);
  };
  bool ChangeParent(Rule rule, Rule newParent) {
    return RuleNodeManager::ChangeParent(rule, newParent);
  };
  Rule GetRoot() { return RuleNodeManager::GetRoot(); };

  Rule GetRule(QString ruleName) { return RuleNodeManager::GetRule(ruleName); };
  Rule GetRule(int id) {
    return RuleNodeManager::GetRule(id);
  }; // TODO add node hierarchy
  int GetRuleIndex(QString ruleName) {
    return RuleNodeManager::GetRuleIndex(ruleName);
  };

  int GetRuleCount() {
    return RuleNodeManager::GetRuleCount();
  }; // TODO add node hierarchy
  Rule CreateRule(QString name, QString desc, Rule parent,
                  bool useParentTemplate, bool chapter = false) {
    return RuleNodeManager::CreateRule(name, desc, parent, useParentTemplate,
                                       chapter);
  };

  /**
   * @brief Set the Chapter object, default to root if not set
   * the rule has to have chapter set to to true
   *
   * @param newChapter
   */
  void SetChapter(Rule newChapter = nullptr) {
    return RuleNodeManager::SetChapter(newChapter);
  };

  Rule LoadRule(QJsonObject obj) { return RuleNodeManager::LoadRule(obj); };
  void LoadFromFile(QString path) {
    return RuleNodeManager::LoadFromFile(path);
  };
  void SaveToFile(QString path) { return RuleNodeManager::SaveToFile(path); };

  bool NameTaken(QString name) { return RuleNodeManager::NameTaken(name); };
};
} // namespace Rules