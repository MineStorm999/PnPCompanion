//
// Created by Spaced Viking on 25.06.2026
//

#include "RuleNodeHintModel.h"
#include "RuleNodeManager.h"
#include "utils.h"

namespace Rules {
RuleNodeHintModel::RuleNodeHintModel(QObject *parent) : QObject{parent} {}
QString RuleNodeHintModel::getName() const {
  if (!m_hint) {
    return "";
  }
  return m_hint->name();
}
QString RuleNodeHintModel::getFormattedText() const {
  if (!m_hint) {
    return "";
  }
  return m_hint->formattedText();
}

void RuleNodeHintModel::setHint(QString hint) {
  m_hint = RuleNodeManager::GetRule(hint);
}

void RuleNodeHintModel::save() {
  RuleNodeManager::SaveToFile(Utils::GetExePath().toString() +
                              ("/Saves/default.json"));
}

} // namespace Rules