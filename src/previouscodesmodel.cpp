#include "previouscodesmodel.h"

PreviousCodesModel::PreviousCodesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    this->settings = new QSettings();

    previousCodesData = settings->value("previousCodes").toList();
}

QVariant PreviousCodesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    return QVariant();
}

int PreviousCodesModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return previousCodesData.count();
}

QVariant PreviousCodesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    QVariantMap indexMap = previousCodesData.at(index.row()).toMap();
    return indexMap[roleNames().value(role)];
}

QHash<int, QByteArray> PreviousCodesModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TextRole] = "text";
    names[ImageSrcRole] = "imageSrc";
    names[TimestampRole] = "timestamp";

    return names;
}

void PreviousCodesModel::saveData(QString text, QString src)
{
    qDebug() << "Saving" << text << src;

    QVariantMap unit;
    unit[roleNames().value(TextRole)] = text;
    unit[roleNames().value(ImageSrcRole)] = src;
    unit[roleNames().value(TimestampRole)] = QDateTime::currentDateTime();

    previousCodesData.push_front(unit);
    if(previousCodesData.count() > 10)
    {
        previousCodesData.pop_back();
    }
    this->settings->setValue("previousCodes",previousCodesData);
    emit dataChanged(createIndex(0,0),createIndex(this->previousCodesData.count()-1,0),roleNames().keys().toVector());
}
