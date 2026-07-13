//
// Created by Spaced Viking on 29.06.2026
//

#pragma once

#include "RuleNode.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <qabstractitemmodel.h>
#include <qtmetamacros.h>
namespace Rules {

//! [0]
class RuleNodeTreeModel : public QAbstractItemModel {
  Q_OBJECT
  QML_ELEMENT
public:
  enum TreeModelRoles { NameRole = Qt::UserRole + 1 };

  explicit RuleNodeTreeModel(QObject *parent = 0);

  /* QAbstractItemModel interface */
  QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
  Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  QModelIndex
  index(int row, int column,
        const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
  int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  int columnCount(const QModelIndex &parent = QModelIndex()) const
      Q_DECL_OVERRIDE;
  QHash<int, QByteArray> roleNames() const override;

  void ChildrenAdded(RuleNode *parent, RuleNode *child);
  Q_INVOKABLE QModelIndex getRuleIndex(QString name);

  Q_INVOKABLE void save(); // TODO Move qml saving somewhere else

private:
  QHash<int, QByteArray> m_roleNameMapping;
  QMap<RuleNode *, QModelIndex> m_idMap;
};
} // namespace Rules