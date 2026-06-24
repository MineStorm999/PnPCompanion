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
  static void ChangeName(Rule rule, QString newName);
  static Rule GetRule(QString ruleName);
  static Rule CreateRule(QString name, QString desc, QString parentName,
                         bool useParentTemplate);

  static Rule CreateRule(QString name, QString desc, Rule parent,
                         bool useParentTemplate);

  static bool NameTaken(QString name);
};
} // namespace Rules