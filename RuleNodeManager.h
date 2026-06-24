//
// Created by Spaced Viking on 24.06.2026
//

#pragma once
#include "RuleNode.h"
#include <qcontainerfwd.h>

namespace Rules {
class RuleNodeManager {
public:
  static void NameChanged(std::shared_ptr<Rules::RuleNode> rule, QString old);
};
} // namespace Rules