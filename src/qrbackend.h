#ifndef QRBACKEND_H
#define QRBACKEND_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QDateTime>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QImage>

class QrBackend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString imageSrc MEMBER imageSrc NOTIFY imageUpdated)
    Q_PROPERTY(QString inputText MEMBER inputText)


public:
    explicit QrBackend(QObject *parent = nullptr);
private:
    QString inputText;
    QString imageSrc;
    QString textUsed;
    bool imageAlreadyGenerated;
private:
    void generateQRFromString(QString input);
public slots:
    void generate();
    void regenerate();

signals:
    void imageUpdated();
};

#endif // QRBACKEND_H
