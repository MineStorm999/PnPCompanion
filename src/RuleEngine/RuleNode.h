//
// Created by Spaced Viking on 05.06.2026
//

#pragma once
#include <QObject>

namespace Rules {
class RuleNode : QObject {
  Q_OBJECT
public:
  explicit RuleNode(QObject *parent = nullptr);
};
} // namespace Rules