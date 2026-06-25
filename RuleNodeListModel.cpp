//
// Created by Spaced Viking on 06.06.2026
//

#include "RuleNodeListModel.h"
#include "RuleNode.h"
#include <qlogging.h>

namespace Rules {
RuleNodeListModel::RuleNodeListModel(QObject *parent)
    : QAbstractListModel{parent} {}

void RuleNodeListModel::addNode(RuleNode *node, int i) {
  if (i == -1) {
    i = rowCount();
  }
  beginInsertRows(QModelIndex(), i, i);
  m_ruleNodes.append(node);
  endInsertRows();
}
void RuleNodeListModel::addNode(QString n_name, QString n_desc, int i) {
  addNode(new RuleNode(nullptr, n_name, n_desc), i);
}

int RuleNodeListModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_ruleNodes.count();
}

QVariant RuleNodeListModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= m_ruleNodes.count())
    return QVariant();

  RuleNode *node = m_ruleNodes[index.row()];
  switch ((RuleNodeRoles)role) {
  case NameRole:
    return node->name();
  case DescriptionRole:
    return node->description();
  case FormattedDescriptionRole:
    return node->formattedText();
  }
  return QVariant();
}
bool RuleNodeListModel::setData(const QModelIndex &index, const QVariant &value,
                                int role) {
  if (!index.isValid()) {
    return false;
  }
  RuleNode *node = m_ruleNodes[index.row()];
  switch ((RuleNodeRoles)role) {
  case NameRole:
    if (!value.canConvert<QString>())
      return false;
    node->setname(value.toString());
    emit dataChanged(index, index, {Qt::EditRole, Qt::DisplayRole, NameRole});
    return true;
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
  }
  return false;
};
} // namespace Rules