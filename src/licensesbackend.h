#ifndef LICENSESBACKEND_H
#define LICENSESBACKEND_H

#include <QObject>

class LicensesBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString qrCodeLic READ getQRCodeLicense)
    Q_PROPERTY(QString softwareLic READ getSoftwareLicense)
    Q_PROPERTY(QString materialLic READ getMaterialIconsLicense)

public:
    explicit LicensesBackend(QObject *parent = nullptr);

public slots:
    QString getQRCodeLicense();
    QString getMaterialIconsLicense();
    QString getSoftwareLicense();
signals:

};

#endif // LICENSESBACKEND_H
