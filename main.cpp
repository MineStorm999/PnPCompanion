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

/**
 * @brief Dump children of a QObject
 *
 * @param obj
 * @param depth
 */
void DumpChildren(QObject *obj, int depth) {
  auto &c = obj->children(); // get children of the QObject

  QString out = ""; // init empty string

  for (int i = 0; i < depth; i++) { // indent one level deeper
    out += "---";
  }

  for (auto &ch : c) { // dump children recursively
    QString s = ch->objectName();
    qDebug() << out + s;
    DumpChildren(ch, depth + 1);
  }
}

int main(int argc, char *argv[]) {
  // qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

  Rules::RuleNodeManager::Init(); // initialize the rule node manager
  // load rules from sample file

  QGuiApplication app(argc, argv); // create application instance

  QQmlApplicationEngine engine; // create qml application instance
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection); // connect object creation failed signal to
                             // application exit function

  engine.loadFromModule(
      "PnPCompanion",
      "Main"); // load main qml module into the QML Application Engine

  Rules::RuleNodeManager::LoadFromFile(Utils::GetRelativePath(
      "/Saves/default.json")); // Load rules from sample file
  return app.exec(); // start application event loop and exit when done.
}
