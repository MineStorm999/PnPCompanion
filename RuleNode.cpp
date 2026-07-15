//
// Created by Spaced Viking on 05.06.2026
//

#include "RuleNode.h"
#include "RuleNodeManager.h"
#include <QDebug>
#include <QObject>
#include <QRegularExpression>
#include <QVector>
#include <cstddef>
#include <qjsonobject.h>

namespace Rules {
RuleNode::RuleNode(RuleNode *parent, QString n_name, QString n_desc)
    : QObject{parent} {
  setname(n_name);
  setdescription(n_desc);
  if (parent) {
    setdepth(parent->depth() + 1);
  }
}

void RuleNode::setname(QString newname) // implementation
{
  if (m_name == newname)
    return;
  _setname(newname);
  // RuleNodeManager::ChangeName(m_this, newname);
}
void RuleNode::_setname(QString newname) // implementation
{
  if (m_name == newname)
    return;
  m_name = newname;
  m_changed = true;
  emit nameChanged();
}
const QString RuleNode::name() // implementation
{
  return m_name;
}
void RuleNode::setdescription(QString newdescription) // implementation
{
  if (m_description == newdescription)
    return;
  m_description = newdescription;
  m_changed = true;
  setformattedText(newdescription);
  emit descriptionChanged();
}

const QString RuleNode::description() // implementation
{
  return m_description;
}

/**
 * @brief Set the template for this rule node.
 *
 * @param newTemplate
 */
void RuleNode::setTemplate(RuleNode *newTemplate) // implementation
{
  if (m_Template == newTemplate)
    return;
  m_Template = newTemplate;
  m_changed = true;
  emit TemplateChanged();
}

RuleNode *RuleNode::Template() // implementation
{
  return m_Template;
}

void RuleNode::LinkNameChanged() {
  Rule link =
      RuleNodeManager::GetRule(((RuleNode *)sender())->name()); // get rule node
  if (!link) { // return if no rule
    return;
  }

  if (!m_links.contains(link)) { // return and disconnect, if not linked
    disconnect(link, &RuleNode::nameChanged, this, &RuleNode::LinkNameChanged);
    return;
  }

  std::string editedUnformattedText = ""; // init edited unformatted text
  std::sort(m_links[link].begin(), m_links[link].end()); // sort id list
  std::string rawUnformattedText =
      m_description.toStdString(); // get unformatted text

  int lastId = 0;
  for (int id : m_links[link]) {
    editedUnformattedText += rawUnformattedText.substr(
        lastId, (id + 1) - lastId); // append edited unformatted text

    editedUnformattedText +=
        "{" + link->name().toStdString() + "}"; // add new name

    lastId = rawUnformattedText.find_first_of('}', id) + 1; // update last id
  }
  editedUnformattedText +=
      rawUnformattedText.substr(lastId); // append edited unformatted text

  this->setdescription(
      QString::fromStdString(editedUnformattedText)); // update description
}
const QRegularExpression LINK_PATTERN("\\{(.*?)\\}");

void RuleNode::setformattedText(QString unformattedText) {
  QString formattedText;
  QRegularExpressionMatchIterator it =
      LINK_PATTERN.globalMatch(unformattedText);

  // Cleanup old links
  for (auto [linkRule, linkPtr] : m_links.asKeyValueRange()) {
    disconnect(linkRule, &RuleNode::nameChanged, this,
               &RuleNode::LinkNameChanged);
  }
  m_links.clear();

  int lastIndex = 0;

  while (it.hasNext()) {
    QRegularExpressionMatch match = it.next();

    // Append text before the match
    formattedText +=
        unformattedText.mid(lastIndex, match.capturedStart() - lastIndex);

    // Extract the rule name from the capture group
    QString ruleName = match.captured(1);

    // Check if rule exists and create link
    if (RuleNodeManager::NameTaken(ruleName)) {
      Rule rule = RuleNodeManager::GetRule(ruleName);
      if (!m_links.contains(rule)) {
        connect(rule, &RuleNode::nameChanged, this, &RuleNode::LinkNameChanged);
      }
      m_links[rule].push_back(match.capturedStart() - 1);

      // Add markdown link
      formattedText += "[" + ruleName + "](" + ruleName + ")";
    } else {
      // Keep original text if rule doesn't exist
      formattedText += match.captured();
    }

    lastIndex = match.capturedEnd();
  }

  // Append remaining text after last match
  formattedText += unformattedText.mid(lastIndex);

  m_formattedText = formattedText;
  m_changed = true;
  emit formattedTextChanged();
}

void RuleNode::_setformattedText() // implementation
{
  setformattedText(m_description);
}

const QString RuleNode::formattedText() // implementation
{
  return m_formattedText;
}

// implementation of depth
void RuleNode::setdepth(int newdepth) // implementation
{
  if (m_depth == newdepth)
    return;
  m_depth = newdepth;
  m_changed = true;
  emit depthChanged();
}

const int RuleNode::depth() // implementation
{
  return m_depth;
}

QJsonObject RuleNode::Save() {
  /* if (!m_changed) { // TODO cache changes
     return {};
   }*/

  QJsonObject obj;
  obj.insert("name", name());
  obj.insert("description", description());
  if (!parent()) {
    obj.insert("parent", "---");
  } else {
    obj.insert("parent", ((Rule)parent())->name());
  }
  return obj;
}

void RuleNode::setchapter(bool newchapter) {
  if (m_chapter == newchapter)
    return;
  m_chapter = newchapter;
  emit chapterChanged();
}

const bool RuleNode::chapter() { return m_chapter; }
} // namespace Rules