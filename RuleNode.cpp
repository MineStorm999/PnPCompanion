//
// Created by Spaced Viking on 05.06.2026
//

#include "RuleNode.h"
#include "RuleNodeManager.h"
namespace Rules {
RuleNode::RuleNode(RuleNode *parent, QString n_name, QString n_desc)
    : QObject{parent} {
  setname(n_name);
  setdescription(n_desc);
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
  emit descriptionChanged();
}

const QString RuleNode::description() // implementation
{
  return m_description;
}
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
void RuleNode::setformattedText(QString newformattedText) // implementation
{
  if (m_formattedText == newformattedText)
    return;
  m_formattedText = newformattedText;
  emit formattedTextChanged();
}

const QString RuleNode::formattedText() // implementation
{
  return m_formattedText;
}
} // namespace Rules