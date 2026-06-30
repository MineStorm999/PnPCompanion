

#include "RuleNodeTreeModel.h"
#include "RuleNode.h"
#include "RuleNodeManager.h"

#include <QStringList>
#include <qabstractitemmodel.h>

namespace Rules {
RuleNodeTreeModel::RuleNodeTreeModel(QObject *parent)
    : QAbstractItemModel(parent) {
  m_roleNameMapping[NameRole] = "name";

  m_idMap[RuleNodeManager::GetRoot()] = QModelIndex{};

  qDebug() << "Root:" << RuleNodeManager::GetRoot();
  qDebug() << "Root children count:"
           << (RuleNodeManager::GetRoot()
                   ? RuleNodeManager::GetRoot()->children().size()
                   : 0);

  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleChildAdded, this,
          &RuleNodeTreeModel::ChildrenAdded);
}

int RuleNodeTreeModel::columnCount(const QModelIndex &parent) const {
  return 1;
}

void RuleNodeTreeModel::ChildrenAdded(RuleNode *parent, RuleNode *child) {
  beginInsertRows(m_idMap[parent], parent->children().size() - 1,
                  parent->children().size() - 1);
  endInsertRows();
  m_idMap[child] = index(parent->children().size() - 1, 0, m_idMap[parent]);
}

QVariant RuleNodeTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role != NameRole)
    return QVariant();

  Rule rule = static_cast<Rule>(index.internalPointer());

  return rule->name();
}

QVariant RuleNodeTreeModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return QVariant(); // RuleNodeManager::GetRoot()->data(section);

  return QVariant();
}

Qt::ItemFlags RuleNodeTreeModel::flags(const QModelIndex &index) const {
  return QAbstractItemModel::flags(index);
}
/*
QVariant RuleNodeTreeModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return rootItem->data(section);

  return QVariant();
}*/

QModelIndex RuleNodeTreeModel::index(int row, int column,
                                     const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  Rule parentItem;

  if (!parent.isValid())
    parentItem = RuleNodeManager::GetRoot();
  else
    parentItem = static_cast<Rule>(parent.internalPointer());

  Rule childItem = (Rule)parentItem->children()[row];

  if (childItem)
    return createIndex(row, column, childItem);
  else
    return QModelIndex();
}

QModelIndex RuleNodeTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();

  Rule childItem = static_cast<Rule>(index.internalPointer());
  Rule parentItem = (Rule)childItem->parent();

  if (parentItem == RuleNodeManager::GetRoot())
    return QModelIndex();

  return createIndex(parentItem->parent()->children().indexOf(parentItem), 0,
                     parentItem);
}

int RuleNodeTreeModel::rowCount(const QModelIndex &parent) const {
  Rule parentItem;
  if (parent.column() > 0)
    return 0;

  if (!parent.isValid())
    parentItem = RuleNodeManager::GetRoot();
  else
    parentItem = static_cast<Rule>(parent.internalPointer());

  return parentItem->children().size();
}
//! [8]

QHash<int, QByteArray> RuleNodeTreeModel::roleNames() const {
  return m_roleNameMapping;
}

} // namespace Rules
