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

  /**
   * @brief Construct a new Rule Node Tree Model object
   *
   * @param parent
   */
  explicit RuleNodeTreeModel(QObject *parent = 0);
  /**
   * @brief data function, returns data for the given item and the specified
   * data
   *
   * @param index
   * @param role
   * @return QVariant
   */
  QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
  /**
   * @brief returns the flags
   *
   * @param index
   * @return Qt::ItemFlags
   */
  Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
  /**
   * @brief returns the header data
   *
   * @param section
   * @param orientation
   * @param role
   * @return QVariant
   */
  QVariant headerData(int section, Qt::Orientation orientation,

                      int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  /**
   * @brief return the index for the given row and column in parent index.
   *
   * @param row
   * @param column
   * @param parent
   * @return QModelIndex
   */
  QModelIndex
  index(int row, int column,
        const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  /**
   * @brief returns the parent index for a given child.
   *
   *
   * @param index
   * @return QModelIndex
   */
  QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
  /**
   * @brief returns the number of rows in a given parent.
   *
   * @param parent
   * @return int
   */
  int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  /**
   * @brief returns the number of columns in a given parent.
   *
   * @param parent
   * @return int
   */
  int columnCount(const QModelIndex &parent = QModelIndex()) const
      Q_DECL_OVERRIDE;
  /**
   * @brief returns the role names for this model.
   * @return QHash<int, QByteArray>
   */
  QHash<int, QByteArray> roleNames() const override;

  /**
   * @brief childrenAdded is called when a child node has been added to the
   * tree.
   *
   * @param parent
   * @param child
   */
  void ChildrenAdded(RuleNode *parent, RuleNode *child);

  void _parentChanged(RuleNode *rule, RuleNode *oldParent, int oldIndex,
                      RuleNode *newParent);

  /**
   * @brief Get the Rule Index object for a given rule.
   *
   * @param name
   * @return Q_INVOKABLE
   */
  Q_INVOKABLE QModelIndex getRuleIndex(QString name);
  /**
   * @brief save
   *
   * @return Q_INVOKABLE
   */
  /* // TODO CLEAN Q_INVOKABLE void save(); // TODO Move qml saving somewhere
   * else*/

private:
  QHash<int, QByteArray> m_roleNameMapping;
  QMap<RuleNode *, QModelIndex> m_idMap;
};
} // namespace Rules