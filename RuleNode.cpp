//
// Created by Spaced Viking on 01.06.2026
//

#include "RuleNode.h"

RuleNode::RuleNode(QQuickItem *parent) : QQuickItem{parent} {}
// declaration
QString RuleNode::text() const // implementation
{
  return m_text;
}
void RuleNode::settext(QString newtext) // implementation
{
  if (m_text == newtext)
    return;
  m_text = newtext;
  emit textChanged();
}