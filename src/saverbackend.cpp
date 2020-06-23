#include "saverbackend.h"

SaverBackend::SaverBackend(QObject *parent) : QObject(parent)
{

}

void SaverBackend::saveToDisk()
{
#ifdef Q_OS_ANDROID
    this->saveDefaultFolderAndroid();
#else
    emit requestFolder();
#endif
}

#ifdef Q_OS_ANDROID
void SaverBackend::saveDefaultFolderAndroid()
{
    QUrl srcUrl(this->imageSrc);

    QStringList permissions({"android.permission.WRITE_EXTERNAL_STORAGE"});
    QtAndroid::PermissionResultMap results = QtAndroid::requestPermissionsSync(permissions,0);
    if ( results[permissions.first()] == QtAndroid::PermissionResult::Denied)
    {
        return;
    }
    QUrl destFolderUrl(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
    QDir destDir(destFolderUrl.toString().append("/").append("MisterQR"));
    if(!destDir.exists())
    {
        destDir.mkpath(destDir.path());
    }
    QUrl destUrl = QUrl(QString("file:/%1/%2").arg(destDir.absolutePath(),srcUrl.fileName()));
    bool status = QFile::copy(srcUrl.toLocalFile(), destUrl.toLocalFile());
    if(status)
    {
        QRecodeUtils::showNotification(destUrl.toString().prepend("QR Saved To: "));
    }
    else
    {
        QRecodeUtils::showNotification(QString("QR could not be saved!"));
    }
}
#else
void SaverBackend::saveInFolder(QString folder)
{
    QUrl srcUrl(this->imageSrc);
    QDir destDir(folder);
    QUrl destUrl = QUrl(destDir.filePath(srcUrl.fileName()));
    bool status = QFile::copy(srcUrl.toLocalFile(), destUrl.toLocalFile());
}
#endif
