#include "RuleNode.h"
#include "RuleNodeListModel.h"
#include "RuleNodeManager.h"
#include "utils.h"
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
  // qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

  Rules::RuleNodeManager::Init();
  // load rules from sample file

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("PnPCompanion", "Main");

  Rules::RuleNodeManager::LoadFromFile(
      Utils::GetRelativePath("/Saves/default.json"));
  return app.exec();
}
