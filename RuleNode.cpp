//
// Created by Spaced Viking on 05.06.2026
//

#include "RuleNode.h"
namespace Rules {
RuleNode::RuleNode(QObject *parent) : QObject{parent} {}

void RuleNode::setname(QString newname) // implementation
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

const RuleNode *RuleNode::Template() // implementation
{
  return m_Template;
}

void RuleNode::setimportantAttributes(
    QVector<RuleNode *> newimportantAttributes) // implementation
{
  if (m_importantAttributes == newimportantAttributes)
    return;
  m_importantAttributes = newimportantAttributes;
  emit importantAttributesChanged();
}

const QVector<RuleNode *> RuleNode::importantAttributes() // implementation
{
  return m_importantAttributes;
}
} // namespace Rules