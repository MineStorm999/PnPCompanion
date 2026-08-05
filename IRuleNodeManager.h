//
// Created by Spaced Viking on 05.08.2026
//

#pragma once
#include "RuleNode.h"
#include <QObject>
#include <qqmlintegration.h>

namespace Rules {
class IRuleNodeManager : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit IRuleNodeManager(QObject *parent = nullptr);

signals:
  void ruleNameChanged(RuleNode *rule);
  void ruleParentChanged(RuleNode *rule, RuleNode *oldParent, int oldIndex,
                         RuleNode *newParent);
  void ruleDataChanged(RuleNode *rule);
  void ruleChildAdded(RuleNode *parent, RuleNode *child);
  void ruleChapterChanged(RuleNode *oldChapter, RuleNode *newChapter,
                          int oldRuleCount);

public slots:
  bool changeName(RuleNode *rule, QString newName);
  bool changeParent(RuleNode *rule, RuleNode *newParent);
  RuleNode *getRoot();

  RuleNode *getRule(QString ruleName);
  RuleNode *getRule(int id); // TODO add node hierarchy
  int getRuleIndex(QString ruleName);

  QStringList getRulesNames();
  int getRuleCount(); // TODO add node hierarchy
  RuleNode *createRule(QString name, QString desc, RuleNode *parent,
                       bool useParentTemplate, bool chapter = false);

  /**
   * @brief Set the Chapter object, default to root if not set
   * the rule has to have chapter set to to true
   *
   * @param newChapter
   */
  void setChapter(RuleNode *newChapter = nullptr);

  RuleNode *loadRule(QJsonObject obj);
  void loadFromFile(QString path);
  void saveToFile(QString path = "");

  bool nameTaken(QString name);

public: // INTERNAL
  void _ruleNameChanged(RuleNode *rule);
  void _ruleParentChanged(RuleNode *rule, RuleNode *oldParent, int oldIndex,
                          RuleNode *newParent);
  void _ruleDataChanged(RuleNode *rule);
  void _ruleChildAdded(RuleNode *parent, RuleNode *child);
  void _ruleChapterChanged(RuleNode *oldChapter, RuleNode *newChapter,
                           int oldRuleCount);
};
} // namespace Rules