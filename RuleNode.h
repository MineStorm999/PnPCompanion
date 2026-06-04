//
// Created by Spaced Viking on 01.06.2026
//

#pragma once
#include <QQuickItem>
#include <qqmlintegration.h>

class RuleNode : QQuickItem {
public:
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(QString text READ text WRITE settext NOTIFY textChanged FINAL)

  explicit RuleNode(QQuickItem *parent = nullptr);

  void settext(QString newtext);
  QString text() const;
signals:
  void textChanged();

private:
  QString m_text;
};
