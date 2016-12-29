#include "networkimage.h"
#include <QDebug>

void NetworkImage::into(QGraphicsView *&graphicsView)
{
    this->graphicsView = graphicsView;

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleImageReady(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(this->url)));
}

void NetworkImage::handleImageReady(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        QGraphicsScene *scene = new QGraphicsScene();
        QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem();
        pixmapItem->setPixmap(pixmap);
        scene->addItem(pixmapItem);
        this->graphicsView->resize(pixmap.width(), pixmap.height());
        // FIXME:
        // this->graphicsView->fitInView(pixmapItem);
        this->graphicsView->setScene(scene);
        this->graphicsView->show();
    } else {
        qDebug("network error %s", reply->errorString().toStdString().c_str());
    }

    QDebug(QtDebugMsg) << "handleImageReady " << url.toStdString().c_str();
}

NetworkImage* NetworkImage::load(QString url)
{
    NetworkImage *networkImage = new NetworkImage(url);
    return networkImage;
}
