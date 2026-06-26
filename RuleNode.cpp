//
// Created by Spaced Viking on 05.06.2026
//

#include "RuleNode.h"
#include "RuleNodeManager.h"
#include <qlogging.h>
#include <qobject.h>
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

// implementation of formattedText
void RuleNode::setformattedText(QString unformattedText) // implementation
{
  QString formattedText;
  std::string unformattedTextRaw = unformattedText.toStdString();

  // links
  auto openingBracket = unformattedTextRaw.find_first_of('{');
  while (openingBracket != std::string::npos) {
    auto closingBracket = unformattedTextRaw.find_first_of('}');
    if (closingBracket == std::string::npos) {
      break;
    }
    formattedText += unformattedTextRaw.substr(0, openingBracket);
    // qDebug() << "formatted text: " << formattedText;

    QString stringToParse = QString::fromStdString(unformattedTextRaw.substr(
        openingBracket + 1, closingBracket - (openingBracket + 1)));
    // qDebug() << "String to parse: " << stringToParse;

    unformattedTextRaw = unformattedTextRaw.substr(closingBracket + 1);
    openingBracket = unformattedTextRaw.find_first_of('{');

    if (RuleNodeManager::NameTaken(stringToParse)) {
      formattedText += "[" + stringToParse + "](" + stringToParse + ")";
    }
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