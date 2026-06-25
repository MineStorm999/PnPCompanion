//
// Created by Spaced Viking on 25.06.2026
//

#pragma once
#include <QObject>
#include <qqmlintegration.h>

namespace Rules {
class RuleNodeHintModel : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit RuleNodeHintModel(QObject *parent = nullptr);

  Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value,
                           int role) override;
};
} // namespace Rules