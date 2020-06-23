#ifndef SAVERBACKEND_H
#define SAVERBACKEND_H

#include <QObject>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QUrl>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QStandardPaths>
#endif

#include "qrecodeutils.h"


class SaverBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imageSrc MEMBER imageSrc)
    Q_PROPERTY(QString destFolder MEMBER destFolder)

public:
    explicit SaverBackend(QObject *parent = nullptr);
private:

    QString imageSrc;
    QString destFolder;
public slots:
    void saveToDisk();

#ifdef Q_OS_ANDROID
    void saveDefaultFolderAndroid();
#else
    void saveInFolder(QString folder);
#endif

signals:
    void requestFolder();

};

#endif // SAVERBACKEND_H
