#include "qrbackend.h"

#include "QrCode.hpp"
using namespace qrcodegen;

QrBackend::QrBackend(QObject *parent) : QObject(parent)
{
    inputText = "";
    this->imageAlreadyGenerated = false;
}

void QrBackend::generateQRFromString(QString input)
{

    QSettings settings;
    QString format = settings.value("imageFormatText",QVariant("PNG")).toString();
    bool includeText = settings.value("includeText",QVariant(false)).toBool();
    int imgSz = settings.value("imageSize",QVariant(320)).toInt();

    QrCode qr = QrCode::encodeText(input.toLatin1(), QrCode::Ecc::MEDIUM);
    // Manual operation
    QSize sz(imgSz,imgSz);
    const int s=qr.getSize()>0?qr.getSize():1;
    const double w=sz.width();
    const double h=sz.height();
    const double aspect=w/h;
    const double size=((aspect>1.0)?h:w);
    const double scale=size/(s+2);

    int text_height = 0;
    if(includeText)
    {
        text_height = sz.height()/8;
    }
    QColor fg = Qt::black;
    QImage image(w, h + text_height, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);
    QPainter painter;
    painter.begin(&image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(fg);
    qDebug() << s;
    for(int y=0; y<s; y++) {
        for(int x=0; x<s; x++) {
            const int color=qr.getModule(x, y);  // 0 for white, 1 for black
            if(0!=color) {
                const double rx1=(x+1)*scale, ry1=(y+1)*scale;
                QRectF r(rx1, ry1, scale, scale);
                painter.drawRects(&r,1);
            }
        }
    }
    if(includeText)
    {
        painter.setPen(Qt::black);
        QFont f = painter.font();
        f.setPointSize(40);
        painter.setFont(f);
        float factor = float(sz.width()) / float(painter.fontMetrics().width(input));
        float factorv = float(text_height) / float(painter.fontMetrics().height());

        float myfactor = std::min(factor,factorv);
        f = painter.font();
        f.setPointSizeF(f.pointSizeF()*myfactor);
        painter.setFont(f);
        int text_width = painter.fontMetrics().width(input);
        int margin = (sz.width() - text_width)/2;
        painter.drawText(QRect(margin,sz.height(),sz.width(),text_height),input);
    }
    painter.end();

    QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
    QString filename = QString("image_%1.%2").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss"),format);

    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug() << path;
    QDir pathFolder(path);
    if (!pathFolder.exists())
    {
        QDir().mkpath(path);
    }
    auto filePath= path + "/" + filename;
    qDebug() << "Save was " << image.save(filePath,0) << filePath;
    this->imageSrc = QString("file:%1").arg(filePath);
    emit imageUpdated();
    this->imageAlreadyGenerated = true;
}
void QrBackend::generate()
{
    this->textUsed = this->inputText;
    this->generateQRFromString(this->textUsed);
}


void QrBackend::regenerate()
{
    if(this->imageAlreadyGenerated)
    {
        this->generateQRFromString(this->textUsed);
    }
}

