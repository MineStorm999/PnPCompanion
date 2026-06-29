//
// Created by Spaced Viking on 05.06.2026
//

#include "RuleNode.h"
#include "RuleNodeManager.h"
#include <QDebug>
#include <QObject>
#include <QVector>

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

// implementation of formattedText
void RuleNode::setformattedText(
    QString unformattedText) // TODO make updating links more effizient
{
  QString formattedText;
  std::string unformattedTextRaw = unformattedText.toStdString();

  for (auto [linkRule, linkPtr] :
       m_links.asKeyValueRange()) { // cleanup old links
                                    // TODO cache (make efficient)
    disconnect(linkRule, &RuleNode::nameChanged, this,
               &RuleNode::LinkNameChanged);
  }
  m_links.clear();

  // links
  auto openBracket =
      unformattedTextRaw.find_first_of('{'); // init first bracket
  auto id = 0;

  while (openBracket !=
         std::string::npos) { // loop until no opening bracket is found
    auto closedBracket =
        unformattedTextRaw.find_first_of('}'); // find next closing bracket
    if (closedBracket == std::string::npos) {  // return if no closing bracket
      break;
    }

    formattedText += unformattedTextRaw.substr(
        0, openBracket); // appending formatted text until the first open
                         // bracket

    QString stringToParse = QString::fromStdString(
        unformattedTextRaw.substr( // get the name of the linked Rule
            openBracket + 1, closedBracket - (openBracket + 1)));

    if (RuleNodeManager::NameTaken(
            stringToParse)) { // if rule exists, add markdown link syntax and
                              // setup internal linking

      Rule rule = RuleNodeManager::GetRule(
          stringToParse); // setup connections if the linked Rules name changes
      if (!m_links.contains(rule)) {
        connect(rule, &RuleNode::nameChanged, this, &RuleNode::LinkNameChanged);
      }
      m_links[rule].push_back(openBracket + id - 1);

      formattedText += "[" + stringToParse + "](" + stringToParse +
                       ")"; // add markdown syntax
    }

    unformattedTextRaw = unformattedTextRaw.substr(
        closedBracket +
        1); // remove formatted text from unfromatted pool (also link syntax)
    openBracket = unformattedTextRaw.find_first_of('{'); // get new bracket id
    id += closedBracket + 1;                             // increment id
  }

  m_formattedText = formattedText + QString::fromStdString(unformattedTextRaw);
  // qDebug() << "Formatted text: " << m_formattedText;
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
  emit depthChanged();
}

const int RuleNode::depth() // implementation
{
  return m_depth;
}
} // namespace Rules