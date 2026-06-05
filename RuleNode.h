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
  Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged FINAL)
  Q_PROPERTY(QString description READ description WRITE setdescription NOTIFY
                 descriptionChanged FINAL)
  Q_PROPERTY(RuleNode *Template READ Template WRITE setTemplate NOTIFY
                 TemplateChanged FINAL)
  Q_PROPERTY(
      QVector<RuleNode *> importantAttributes READ importantAttributes WRITE
          setimportantAttributes NOTIFY importantAttributesChanged FINAL)
  // declarations
  QVector<RuleNode *> m_importantAttributes;
  void setimportantAttributes(
      QVector<RuleNode *> newimportantAttributes); // declaration
  const QVector<RuleNode *> importantAttributes(); // declaration
  // signal
  void importantAttributesChanged();

public:
  explicit RuleNode(QObject *parent = nullptr);

  void setdescription(QString newdescription);
  const QString description();

  void setname(QString newname);
  const QString name();

  void setTemplate(RuleNode *newTemplate);
  const RuleNode *Template();
signals:
  void nameChanged();
  void descriptionChanged();
  void TemplateChanged();

private:
  QString m_name;
  QString m_description;
  RuleNode *m_Template;
};
} // namespace Rules