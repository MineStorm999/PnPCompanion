//
// Created by Spaced Viking on 05.08.2026
//

#include "IRuleNodeManager.h"
#include "RuleNodeManager.h"

namespace Rules {
IRuleNodeManager::IRuleNodeManager(QObject *parent) : QObject{parent} {
  RuleNodeManager::_SetQMLErmitter(this);
}

} // namespace Rules