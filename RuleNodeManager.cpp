//
// Created by Spaced Viking on 24.06.2026
//

#include "RuleNodeManager.h"
#include <QVector>
#include <memory>

namespace Rules {
using Rule = std::shared_ptr<Rules::RuleNode>;
QVector<Rule> ruleNodes;
QMap<QString, Rule> rules;

} // namespace Rules