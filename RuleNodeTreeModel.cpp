

#include "RuleNodeTreeModel.h"
#include "RuleNode.h"
#include "RuleNodeManager.h"

#include "utils.h"
#include <QStringList>
#include <qabstractitemmodel.h>

namespace Rules {
RuleNodeTreeModel::RuleNodeTreeModel(QObject *parent)
    : QAbstractItemModel(parent) {
  m_roleNameMapping[NameRole] = "name"; // init roles

  m_idMap[RuleNodeManager::GetRoot()] = QModelIndex{}; // init tree ids

  /* // DEBUG
    qDebug() << "Root:" << RuleNodeManager::GetRoot();
    qDebug() << "Root children count:"
             << (RuleNodeManager::GetRoot()
                     ? RuleNodeManager::GetRoot()->children().size()
                     : 0);*/

  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleChildAdded, this,
          &RuleNodeTreeModel::ChildrenAdded); // connect child added signal

  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleParentChanged, this,
          &RuleNodeTreeModel::_parentChanged); // connect parent changed signal
}

int RuleNodeTreeModel::columnCount(const QModelIndex &parent) const {
  return 1; // always 1
}

void RuleNodeTreeModel::ChildrenAdded(RuleNode *parent, RuleNode *child) {
  beginInsertRows(m_idMap[parent], parent->children().size() - 1,
                  parent->children().size() -
                      1); // insert row for the new child
  endInsertRows();

  m_idMap[child] = index(parent->children().size() - 1, 0,
                         m_idMap[parent]); // create index for the added child
}

QModelIndex RuleNodeTreeModel::getRuleIndex(QString name) {
  if (!RuleNodeManager::NameTaken(name)) { // name doesnt exist
    return QModelIndex{};
  }
  return m_idMap[RuleNodeManager::GetRule(
      name)]; // return index for the found rule
}
/* // TODO CLEAN
void RuleNodeTreeModel::save() {
  RuleNodeManager::SaveToFile(
      Utils::GetRelativePath("/Saves/default.json")); // save rules to file
  // TODO make rulenodemanager instanced (not static anymore)
}
*/
QVariant RuleNodeTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) // check if index is valid
    return QVariant();

  if (role != NameRole) // check if the requested data is not for name
    return QVariant();

  Rule rule = static_cast<Rule>(index.internalPointer()); // get rule from index

  return rule->name(); // return rule name
}

QVariant RuleNodeTreeModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return QVariant(); // RuleNodeManager::GetRoot()->data(section);

  return QVariant();
}

Qt::ItemFlags RuleNodeTreeModel::flags(const QModelIndex &index) const {
  return QAbstractItemModel::flags(index); // default flags
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
  if (!hasIndex(row, column, parent)) // check index validity
    return QModelIndex();

  Rule parentItem; // init empty parent item

  if (!parent.isValid()) {                   // check if parent is invalid
    parentItem = RuleNodeManager::GetRoot(); // parent is root
  } else {
    parentItem =
        static_cast<Rule>(parent.internalPointer()); // parent is given parent
  }

  if (row >= parentItem->children().size()) {
    return QModelIndex(); // row was invalid
  }

  Rule childItem = (Rule)parentItem->children()[row]; // get child from row

  if (childItem)
    return createIndex(row, column, childItem); // create the index
  else
    return QModelIndex(); // child item was invalid
}

QModelIndex RuleNodeTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) // check index validity
    return QModelIndex();

  Rule childItem =
      static_cast<Rule>(index.internalPointer()); // get child from index
  Rule parentItem = (Rule)childItem->parent();    // get the child's parents

  if (parentItem == RuleNodeManager::GetRoot()) // if parent is root exit
                                                // function with invalid index.
    return QModelIndex();

  return createIndex(parentItem->parent()->children().indexOf(parentItem), 0,
                     parentItem); // return the index of the parent
}

int RuleNodeTreeModel::rowCount(const QModelIndex &parent) const {
  Rule parentItem;
  if (parent.column() > 0) // check if wong column is given
    return 0;

  if (!parent.isValid())
    parentItem =
        RuleNodeManager::GetRoot(); // parent is root when invalid index
  else
    parentItem = static_cast<Rule>(parent.internalPointer());

  return parentItem->children()
      .size(); // return the number of children of the parent
}
//! [8]

QHash<int, QByteArray> RuleNodeTreeModel::roleNames() const {
  return m_roleNameMapping; // return the role names hasmap.
}

void RuleNodeTreeModel::_parentChanged(RuleNode *rule, RuleNode *oldParent,
                                       int oldIndex, RuleNode *newParent) {
  beginMoveRows(m_idMap[oldParent], oldIndex, oldIndex, m_idMap[newParent],
                rule->IndexInParent());
}

} // namespace Rules
