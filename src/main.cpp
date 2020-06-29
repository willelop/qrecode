#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
//#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QTranslator>
#include <QLocale>
#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/qandroidfunctions.h>
#endif
#include "qrbackend.h"
#include "saverbackend.h"
#include "qrecodeutils.h"
#include "licensesbackend.h"
#include "previouscodesmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<QrBackend>("qr.backend",1,0,"QrBackend");
    qmlRegisterType<SaverBackend>("saver.backend",1,0,"SaverBackend");
    qmlRegisterType<QRecodeUtils>("qrecode.utils",1,0,"QRecodeUtils");
    qmlRegisterType<LicensesBackend>("qrecode.licenses",1,0,"LicensesBackend");
    qmlRegisterType<PreviousCodesModel>("qrecode.previous",1,0,"PreviousCodesModel");


    qmlRegisterSingletonType(QUrl("qrc:/qml/Components/Definitions.qml"), "Definitions", 1, 0, "Definitions");

    app.setOrganizationName("willelop");
    app.setApplicationName("QRecode");

    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");


    qDebug() << QLocale().languageToString(QLocale().system().language());
    QTranslator translator;
    // look up e.g. :/translations/myapp_de.qm
    if (translator.load(QLocale(),"QRecode","_",":/translations"))
    {
        QCoreApplication::installTranslator(&translator);
    }
    else
    {
        qDebug() << "could not load file";
    }


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
