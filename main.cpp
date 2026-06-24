#include "RuleNode.h"
#include "RuleNodeListModel.h"
#include "RuleNodeManager.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <qdebug.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qquickview.h>
#include <qvariant.h>

void DumpChildren(QObject *obj, int depth) {
  auto &c = obj->children();
  QString out = "";
  for (int i = 0; i < depth; i++) {
    out += "---";
  }
  for (auto &ch : c) {
    QString s = ch->objectName();
    qDebug() << out + s;
    DumpChildren(ch, depth + 1);
  }
}

int main(int argc, char *argv[]) {
  qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

  Rules::RuleNodeManager::Init();
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("PnPCompanion", "Main");
  auto c = engine.children();
  Rules::RuleNodeListModel *myModel =
      engine.findChild<Rules::RuleNodeListModel *>("test",
                                                   Qt::FindChildrenRecursively);

  for (auto &ch : c) {
    QString s = ch->objectName();
    qDebug() << s;
    DumpChildren(ch, 1);
  } /*
   for (int i = 0; i < 10; i++) {
     myModel->addNode(
         new Rules::RuleNode(nullptr, "Test " + QString::number(i),
                             "Test TESTTESTETS " + QString::number(i)));
   }
 */

  return app.exec();
}
