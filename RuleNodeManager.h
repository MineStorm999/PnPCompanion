//
// Created by Spaced Viking on 24.06.2026
//

#pragma once
#include "RuleNode.h"
#include <QAbstractItemModel>
#include <qobject.h>

namespace Rules {
using Rule = RuleNode *; // std::shared_ptr<Rules::RuleNode>;

class RuleNodeChangesEventEmitter : QObject {
  Q_OBJECT;

signals:
  void ruleNameChanged(Rule rule);
  void ruleParentChanged(Rule rule, Rule oldParent);
  void ruleDataChanged(Rule rule); // TODO implement ruleDataChange
  void ruleChildAdded(Rule parent, Rule child);
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

  static bool NameTaken(QString name);

  static QJsonObject Save(); // TODO saving of rules

  /* WARN accepts QAbstractItemModel, but can only
                         use RuleNodeTreeModel*/
  static RuleNodeChangesEventEmitter *GetSignalErmitter();
  static void Init(QJsonObject *save = nullptr /*TODO saving of rules*/);
};
} // namespace Rules