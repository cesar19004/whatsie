#include "languages.h"
#include "utils.h"
#include <QLibraryInfo>

QString TRANSLATION_FILE_SUFFIX = ".qm";

Languages::Languages(QObject *parent) : QObject{parent} {}

Languages::~Languages() { this->deleteLater(); }

QString Languages::getTranslationPath() {
  QString translationPath;

  QString translationDir = "translations";

  // inside appdata dir /usr/share/org/appname
  QString appdata_path =
      QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation)
          .filter("/usr/share")
          .first();
  translationPath = QString("%1/%2/%3/%4")
                  .arg(appdata_path, QApplication::organizationName(),
                       QApplication::applicationName(), translationDir);
  qDebug() << translationPath;
  if (QDir(translationPath).exists()) {
    return translationPath;
  }

  // next look relative to the executable
  translationPath =
      QCoreApplication::applicationDirPath() + QDir::separator() + translationDir;
  if (QDir(translationPath).exists()) {
    return translationPath;
  }

  // inside the installed Qt directories
  translationPath = QLibraryInfo::location(QLibraryInfo::DataPath) +
              QDir::separator() + translationDir;
  if (QDir(translationPath).exists()) {
    return translationPath;
  }

  return QString();
}

QStringList Languages::getLanguages() {
  QStringList languages;
  QString langPath = getTranslationPath();
  if (langPath.isEmpty()) {
    return languages;
  }
  QDir langDir(langPath);
  if (langDir.exists()) {
    QStringList filters;
    // Look for all *TRANSLATION_FILE_SUFFIX files.
    filters << "*" + TRANSLATION_FILE_SUFFIX;
    langDir.setNameFilters(filters);
    QStringList dictionary_files = langDir.entryList();
    foreach (QString file, dictionary_files) {
      QFileInfo fileInfo(file);
      QString langName = fileInfo.baseName();
      languages.append(langName);
    }
  }
  return languages;
}
