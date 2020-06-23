#include "qrecodeutils.h"

QRecodeUtils::QRecodeUtils(QObject *parent) : QObject(parent)
{

}

void QRecodeUtils::showNotification(const QString &message)
{
#ifdef Q_OS_ANDROID
    showToast(message,LONG);
#else
    showDesktopMessage(message);
#endif
}

#ifdef Q_OS_ANDROID
void QRecodeUtils::showToast(const QString &message, Duration duration)
{
    // all the magic must happen on Android UI thread
    QtAndroid::runOnAndroidThread([message, duration] {
        QAndroidJniObject javaString = QAndroidJniObject::fromString(message);
        QAndroidJniObject toast = QAndroidJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                                            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                                            QtAndroid::androidActivity().object(),
                                                                            javaString.object(),
                                                                            jint(duration));
        toast.callMethod<void>("show");
    });
}
#else
void QRecodeUtils::showDesktopMessage(const QString &message)
{

}
#endif

void QRecodeUtils::changeTheme(QString background, int darktheme)
{
    QColor bgColor(background);

    int androidColor = (bgColor.alpha() & 0xff) << 24 | (bgColor.red() & 0xff) << 16 | (bgColor.green() & 0xff) << 8 | (bgColor.blue() & 0xff);

#ifdef Q_OS_ANDROID

                QtAndroid::runOnAndroidThread([=]()
                {
                    QAndroidJniObject window = QtAndroid::androidActivity().callObjectMethod("getWindow", "()Landroid/view/Window;");
                    window.callMethod<void>("addFlags", "(I)V", 0x80000000);
                    window.callMethod<void>("clearFlags", "(I)V", 0x04000000);
                    window.callMethod<void>("setNavigationBarColor", "(I)V", androidColor); // Desired statusbar color

                    if(darktheme < 1)
                    {
                        QAndroidJniObject decorView = window.callObjectMethod("getDecorView", "()Landroid/view/View;");
                        decorView.callMethod<void>("setSystemUiVisibility", "(I)V", 0x00000010);
                    }
                    else
                    {
                        QAndroidJniObject decorView = window.callObjectMethod("getDecorView", "()Landroid/view/View;");
                        decorView.callMethod<void>("setSystemUiVisibility", "(I)V", 0x00000000);
                    }
                });


#endif
}
