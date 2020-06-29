#ifndef PREVIOUSCODESMODEL_H
#define PREVIOUSCODESMODEL_H

#include <QAbstractListModel>
#include <QSettings>
#include <QVariant>
#include <QDebug>
#include <QTime>

class PreviousCodesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PreviousCodesModel(QObject *parent = nullptr);

    enum CodeRoles {
        TextRole = Qt::UserRole + 1,
        ImageSrcRole,
        TimestampRole
    };
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int,QByteArray> roleNames() const override;

public slots:
    void saveData(QString text, QString src);
private:
    QVariantList previousCodesData;
    QSettings *settings;
};

#endif // PREVIOUSCODESMODEL_H
