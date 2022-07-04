#ifndef LANGUAGES_H
#define LANGUAGES_H

#include <QObject>

class Languages : public QObject {
  Q_OBJECT
public:
  explicit Languages(QObject *parent = nullptr);
  virtual ~Languages();
signals:

public slots:
  static QString getTranslationPath();
  static QStringList getLanguages();
};

#endif // LANGUAGES_H
