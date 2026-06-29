//
// Created by Spaced Viking on 29.06.2026
//

#pragma once

#include "RuleNode.h"
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
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

  void ChildrenChanged(/*RuleNode *parent = nullptr*/);

private:
  QHash<int, QByteArray> m_roleNameMapping;
};
} // namespace Rules