//
// Created by Spaced Viking on 05.06.2026
//

#pragma once
#include <QJsonObject>
#include <QObject>
#include <QQmlComponent>
#include <qjsonobject.h>

namespace Rules {
class RuleNode : public QObject {
  Q_OBJECT
  QML_ELEMENT

  enum Type { eNormal, eUnit, eLocation, eClass, eSpezies };

  Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged FINAL)
  Q_PROPERTY(QString description READ description WRITE setdescription NOTIFY
                 descriptionChanged FINAL)
  Q_PROPERTY(RuleNode *Template READ Template WRITE setTemplate NOTIFY
                 TemplateChanged FINAL)
  Q_PROPERTY(QString formattedText READ formattedText WRITE setformattedText
                 NOTIFY formattedTextChanged FINAL)
  Q_PROPERTY(int depth READ depth WRITE setdepth NOTIFY depthChanged FINAL)

  Q_PROPERTY(
      bool chapter READ chapter WRITE setchapter NOTIFY chapterChanged FINAL)

public:
  explicit RuleNode(RuleNode *parent = nullptr, QString n_name = "",
                    QString n_desc = "");

  void setdescription(QString newdescription);
  const QString description();

  void setname(QString newname);
  const QString name();

  void setTemplate(RuleNode *newTemplate);
  RuleNode *Template();

  Type type() const { return m_type; };
  void setType(Type newType) { m_type = newType; };

  const QString formattedText();
  void setformattedText(QString unformattedText);

  const bool chapter();
  void setchapter(bool newchapter);

  // depth
  void setdepth(int newdepth);
  const int depth();

  QJsonObject Save();
  bool Changed() { return m_changed; };

  int IndexInParent();
public slots:
  void LinkNameChanged();
signals:
  void nameChanged();
  void chapterChanged();
  void descriptionChanged();
  void TemplateChanged();
  // formattedText
  void formattedTextChanged();
  // depth
  void depthChanged();

private:
  QString m_name;
  QString m_description;
  RuleNode *m_Template;
  Type m_type;
  QString m_formattedText;
  int m_depth{-1};

  bool m_changed = false;
  bool m_chapter;

  RuleNode *m_this;

  QMap<RuleNode *, QVector<int>> m_links;

public:
  // internally called
  // internally called
  // internally called
  void _setname(QString newname);
  // internally called
  void _setThis(RuleNode * /*std::shared_ptr<RuleNode>*/ newThis) {
    m_this = newThis;
  };
  // internally called
  Q_INVOKABLE void _setformattedText(); // declaration
};

} // namespace Rules