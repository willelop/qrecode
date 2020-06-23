#ifndef MISTERQRANDROIDUTILS_H
#define MISTERQRANDROIDUTILS_H

#include <QObject>
#include <QColor>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

class QRecodeUtils : public QObject
{
    Q_OBJECT
public:
    explicit QRecodeUtils(QObject *parent = nullptr);
    enum Duration {
        SHORT = 0,
        LONG = 1
    };
    static void showNotification(const QString &message);
#ifdef Q_OS_ANDROID
    static void showToast(const QString &message, Duration duration = LONG);
#else
    static void showDesktopMessage(const QString &message);
#endif
public slots:
    static void changeTheme(QString background, int darktheme);


signals:

};

#endif // MISTERQRANDROIDUTILS_H
