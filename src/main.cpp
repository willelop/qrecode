#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/qandroidfunctions.h>
#endif
#include "qrbackend.h"
#include "saverbackend.h"
#include "qrecodeutils.h"
#include "licensesbackend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<QrBackend>("qr.backend",1,0,"QrBackend");
    qmlRegisterType<SaverBackend>("saver.backend",1,0,"SaverBackend");
    qmlRegisterType<QRecodeUtils>("qrecode.utils",1,0,"QRecodeUtils");
    qmlRegisterType<LicensesBackend>("qrecode.licenses",1,0,"LicensesBackend");

    app.setOrganizationName("willelop");
    app.setApplicationName("QRecode");

    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QQuickStyle::setStyle("Material");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
