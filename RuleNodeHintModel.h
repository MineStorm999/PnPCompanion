//
// Created by Spaced Viking on 25.06.2026
//

#pragma once
#include "RuleNodeManager.h"
#include <QObject>
#include <QQuickItem>
#include <qtmetamacros.h>

namespace Rules {
class RuleNodeHintModel : public QObject {
  Q_OBJECT
  QML_ELEMENT

public:
  explicit RuleNodeHintModel(QObject *parent = nullptr);

  Q_INVOKABLE QString getName() const;
  Q_INVOKABLE QString getFormattedText() const;
  Q_INVOKABLE void setHint(QString hint);
  Q_INVOKABLE void save(); // TODO Move qml saving somewhere else

private:
  Rule m_hint = {nullptr};
};
} // namespace Rules