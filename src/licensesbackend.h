#ifndef LICENSESBACKEND_H
#define LICENSESBACKEND_H

#include <QObject>

class LicensesBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString qrCodeLic READ getQRCodeLicense CONSTANT)
    Q_PROPERTY(QString softwareLic READ getSoftwareLicense CONSTANT)
    Q_PROPERTY(QString materialLic READ getMaterialIconsLicense CONSTANT)

public:
    explicit LicensesBackend(QObject *parent = nullptr);

public slots:
    QString getQRCodeLicense();
    QString getMaterialIconsLicense();
    QString getSoftwareLicense();
signals:

};

#endif // LICENSESBACKEND_H
