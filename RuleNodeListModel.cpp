//
// Created by Spaced Viking on 06.06.2026
//

#include "RuleNodeListModel.h"
#include <QDebug>
#include <RuleNodeManager.h>
namespace Rules {
RuleNodeListModel::RuleNodeListModel(QObject *parent)
    : QAbstractListModel{parent} {
  connect(RuleNodeManager::GetSignalErmitter(),
          &RuleNodeChangesEventEmitter::ruleChildAdded, this,
          &RuleNodeListModel::_addChildNode);
}
/*
void RuleNodeListModel::addNode(RuleNode *node, int i) {
  if (i == -1) {
    i = rowCount();
  }
  beginInsertRows(QModelIndex(), i, i);
  RuleNodeManager::CreateRule(QString name, QString desc, Rule parent, bool
useParentTemplate) endInsertRows();
}*/

void RuleNodeListModel::addNode(QString n_name, QString n_desc, int i) {
  if (RuleNodeManager::NameTaken(n_name)) {
    return;
  }
  if (i == -1) {
    i = rowCount();
  }
  beginInsertRows(QModelIndex(), i, i);
  RuleNodeManager::CreateRule(n_name, n_desc, nullptr /*TODO rule hierarchy*/,
                              false);
  endInsertRows();
}

bool RuleNodeListModel::isNameTaken(QString name) {
  return RuleNodeManager::NameTaken(name);
}

int RuleNodeListModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return RuleNodeManager::GetRuleCount();
}

QVariant RuleNodeListModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= RuleNodeManager::GetRuleCount())
    return QVariant();

  Rule node = RuleNodeManager::GetRule((index).row());

  switch ((RuleNodeRoles)role) {
  case NameRole:
    return node->name();
  case DescriptionRole:
    return node->description();
  case FormattedDescriptionRole:
    return node->formattedText();
  case DepthRole:
    return node->depth();
  case ChapterRole:
    return node->chapter();
  }

  return QVariant();
}

void RuleNodeListModel::addChildNode(QString n_name, QString n_desc,
                                     int parentIndex) {

  if (parentIndex == -1 || parentIndex >= rowCount()) { // invalid id
    return;
  }

  if (RuleNodeManager::NameTaken(n_name)) { // name already taken
    return;
  }

  beginInsertRows(QModelIndex(), parentIndex + 1,
                  parentIndex + 1); // insert rows
  RuleNodeManager::CreateRule(n_name, n_desc,
                              RuleNodeManager::GetRule(parentIndex), false);
  endInsertRows();
}

void RuleNodeListModel::_addChildNode(RuleNode *parent, RuleNode *child) {
  int parentIndex = 0;
  if (parent) {
    parentIndex = getIndex(parent->name());
  }
  beginInsertRows(QModelIndex(), parentIndex + 1, parentIndex + 1);
  endInsertRows();
}

bool RuleNodeListModel::setData(const QModelIndex &index, const QVariant &value,
                                int role) {
  if (!index.isValid()) {
    return false;
  }
  Rule node = RuleNodeManager::GetRule((index).row());
  switch ((RuleNodeRoles)role) {
  case NameRole:
    if (!value.canConvert<QString>())
      return false;
    if (RuleNodeManager::ChangeName(node, value.toString())) {
      emit dataChanged(index, index, {Qt::EditRole, Qt::DisplayRole, NameRole});
      return true;
    }
    return false;

  case DescriptionRole:
    if (!value.canConvert<QString>())
      return false;
    node->setdescription(value.toString());
    emit dataChanged(index, index,
                     {Qt::EditRole, Qt::DisplayRole, DescriptionRole});
    return true;

  case FormattedDescriptionRole:
    qDebug() << "You must not set formatted text directly. Use the description "
                "property instead.";
    return true;

  case DepthRole:
    return false;

  case ChapterRole:
    if (!value.canConvert<bool>())
      return false;
    // node->setchapter(value.toBool());
    return true;
  }

  return false;
};

int RuleNodeListModel::getIndex(QString name) {
  return RuleNodeManager::GetRuleIndex(name);
}
} // namespace Rules