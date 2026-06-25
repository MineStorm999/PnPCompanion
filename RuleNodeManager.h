//
// Created by Spaced Viking on 24.06.2026
//

#pragma once
#include "RuleNode.h"
#include <qcontainerfwd.h>
#include <qobject.h>

namespace Rules {
using Rule = std::shared_ptr<Rules::RuleNode>;
class RuleNodeManager {
public:
  static bool ChangeName(Rule rule, QString newName);
  static Rule GetRule(QString ruleName);
  static Rule GetRule(int id); // TODO add node hierarchy

  static int GetRuleCount(); // TODO add node hierarchy
  // static Rule GetRule(QString ruleName);

  static Rule CreateRule(QString name, QString desc, Rule parent,
                         bool useParentTemplate);

  static bool NameTaken(QString name);

  static QJsonObject Save(); // TODO saving of rules

  static void Init(QJsonObject *save = nullptr /*TODO saving of rules*/);
};
} // namespace Rules