#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QUrl>
namespace Utils {

inline QByteArray ReadFile(QUrl path) {
  if (!path.isValid()) {
    return "";
  }
  QFile userList;

  userList.setFileName("users.json");
  if (userList.open(QIODevice::ReadOnly)) {
    qDebug() << "Read file successfully: " + path.toDisplayString() << "\n";
    return userList.readAll();
  }

  return "";
}

/**
 * @brief write file to path
 *
 * @param path file path
 * @param data data to write
 * @return true on success, otherwise
 * @return false on error
 */
inline bool WriteFile(QUrl path, QByteArray data) {
  if (!path.isValid()) {
    return false;
  }
  QFile userList;

  userList.setFileName("users.json");
  if (!userList.open(QIODevice::WriteOnly)) {
    return false;
  }
  userList.write(data);
  qDebug() << "Wrote file successfully: " + path.toDisplayString() << "\n";
  return true;
}

inline QUrl GetExePath() { return QCoreApplication::applicationDirPath(); }
} // namespace Utils