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

  enum Type { e_normal, e_unit, e_location };

  Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged FINAL)
  Q_PROPERTY(QString description READ description WRITE setdescription NOTIFY
                 descriptionChanged FINAL)
  Q_PROPERTY(RuleNode *Template READ Template WRITE setTemplate NOTIFY
                 TemplateChanged FINAL)

public:
  explicit RuleNode(QObject *parent = nullptr, QString n_name = "",
                    QString n_desc = "");

  void setdescription(QString newdescription);
  const QString description();

  void setname(QString newname);
  const QString name();

  void setTemplate(RuleNode *newTemplate);
  RuleNode *Template();
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