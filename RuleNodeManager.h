//
// Created by Spaced Viking on 24.06.2026
//

#pragma once
#include "RuleNode.h"
#include <QAbstractItemModel>
#include <qjsonobject.h>
#include <qobject.h>
#include <qurl.h>

namespace Rules {
using Rule = RuleNode *; // std::shared_ptr<Rules::RuleNode>;

class RuleNodeChangesEventEmitter : public QObject {
  Q_OBJECT;

signals:
  void ruleNameChanged(Rule rule);
  void ruleParentChanged(Rule rule, Rule oldParent);
  void ruleDataChanged(Rule rule); // TODO implement ruleDataChanged
  void ruleChildAdded(Rule parent, Rule child);
  void ruleChapterChanged(Rule oldChapter,
                          Rule newChapter); // TODO implement ruleChapters
};

class RuleNodeManager {
public:
  static bool ChangeName(Rule rule, QString newName);
  static Rule GetRoot();

  static Rule GetRule(QString ruleName);
  static Rule GetRule(int id); // TODO add node hierarchy
  static int GetRuleIndex(QString ruleName);

  static int GetRuleCount(); // TODO add node hierarchy
  static Rule CreateRule(QString name, QString desc, Rule parent,
                         bool useParentTemplate);

  static Rule LoadRule(QJsonObject obj);
  static void LoadFromFile(QUrl path);
  static void SaveToFile(QUrl path);

  static bool NameTaken(QString name);

  // static QJsonObject Save(); // TODO saving of rules

  static RuleNodeChangesEventEmitter *GetSignalErmitter();
  static void Init(QJsonObject *save = nullptr /*TODO saving of rules*/);
};
} // namespace Rules