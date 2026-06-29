//
// Created by Spaced Viking on 06.06.2026
//

#pragma once
#include "RuleNode.h"
#include <QAbstractListModel>
#include <QVariant>
#include <qnamespace.h>
#include <qtmetamacros.h>

namespace Rules {
class RuleNodeListModel : public QAbstractListModel {
  Q_OBJECT
  QML_ELEMENT
public:
  enum RuleNodeRoles {
    NameRole = Qt::UserRole + 1,
    DescriptionRole,
    FormattedDescriptionRole,
    DepthRole
  };
  explicit RuleNodeListModel(QObject *parent = nullptr);

  // void addNode(RuleNode *node, int i = -1);

  // overridden methods
  Q_INVOKABLE void addNode(QString n_name, QString n_desc,
                           int i = -1); // TODO Handle externally created nodes

  Qt::ItemFlags flags(const QModelIndex &index) const override {
    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
  };
  Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value,
                           int role) override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  Q_INVOKABLE QVariant data(const QModelIndex &index,
                            int role = Qt::DisplayRole) const override;

  Q_INVOKABLE void addChildNode(QString n_name, QString n_desc,
                                int parentIndex);

  Q_INVOKABLE int getIndex(QString name);

protected:
  QHash<int, QByteArray> roleNames() const override {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[FormattedDescriptionRole] = "formattedText";
    roles[DepthRole] = "depth";
    return roles;
  }

private:
  // QList<RuleNode *> m_ruleNodes;
};
} // namespace Rules