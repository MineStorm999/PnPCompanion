//
// Created by Spaced Viking on 05.06.2026
//

#pragma once
#include <QObject>
#include <QQmlComponent>

namespace Rules {
class RuleNode : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit RuleNode(QObject *parent = nullptr);
};
} // namespace Rules