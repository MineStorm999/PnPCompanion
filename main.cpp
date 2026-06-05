#include "RuleNode.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <qobject.h>
#include <qquickview.h>
#include <qvariant.h>
int main(int argc, char *argv[]) {
  qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("PnPCompanion", "Main");

  QList<Rules::RuleNode *> objs;
  for (int i = 0; i < 0; i++) {
    objs.append(new Rules::RuleNode(nullptr, "Test " + QString::number(i),
                                    "Test TESTTESTETS " + QString::number(i)));
  }

  QQuickView view;
  view.setInitialProperties({{"model", QVariant::fromValue(objs)}});

  view.loadFromModule("PnPCompanion", "Rules");
  ((QObject *)&view)->setParent(engine.findChild<QObject *>("rules"));
  // view.show();
  return app.exec();
}
