#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QUrl>
#include <qhashfunctions.h>
namespace Utils {

inline void MakePath(const QString &path) {
  QFileInfo info(path);
  QDir dir;
  dir.mkpath(info.path());
}

inline QString GetRelativePath(const QString &relativePath) {
  QString base = QCoreApplication::applicationDirPath();
  QString full = QDir::cleanPath(base + "/" + relativePath);

  return full;
}

inline QByteArray ReadFile(QString path) {
  QFile userList(path);

  if (userList.open(QIODevice::ReadOnly)) {
    qDebug() << "Read file successfully: " + path << "\n";
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
inline bool WriteFile(QString path, QByteArray data) {
  MakePath(path);
  QFile userList(path);
  if (!userList.open(QIODevice::WriteOnly)) {
    return false;
  }
  userList.write(data);
  qDebug() << "Wrote file successfully: " + path << "\n";
  return true;
}
} // namespace Utils