#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QUrl>
#include <qhashfunctions.h>
namespace Utils {

/**
 * @brief make sure the directory exists
 *
 * @param path
 */
inline void MakePath(const QString &path) {
  QFileInfo info(path);

  QDir dir;
  dir.mkpath(info.path());
}

/**
 * @brief Get the Relative Path object from the base directory
 *
 * @param relativePath
 * @return QString
 */
inline QString GetRelativePath(const QString &relativePath) {
  QString base = QCoreApplication::applicationDirPath();

  QString full = QDir::cleanPath(base + "/" + relativePath);
  return full;
}

/**
 * @brief Read the data from the given file
 *
 * @param path
 * @return QByteArray
 */
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