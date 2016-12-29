#ifndef NETWORKIMAGE_H
#define NETWORKIMAGE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QChar>

class NetworkImage : public QObject
{
    Q_OBJECT
public:
    explicit NetworkImage(QObject *parent = 0);
    NetworkImage(const QString& url) {
        NetworkImage::url = (QString("https:") + QString(url));
    }

    static NetworkImage* load(QString url);
    void into(QGraphicsView* & graphicsView);

signals:

public slots:
    void handleImageReady(QNetworkReply *reply);

private:
    QString url;
    QGraphicsView* graphicsView;
};

#endif // NETWORKIMAGE_H
