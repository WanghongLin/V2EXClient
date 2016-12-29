#include "topicinfo.h"

TopicInfo::TopicInfo(QObject *parent) : QObject(parent)
{

}

TopicInfo* TopicInfo::load(QString url)
{
    TopicInfo *topicInfo = new TopicInfo(url);

    return topicInfo;
}

void TopicInfo::into(QListView *listView)
{
    this->listView = listView;

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleTopicReady(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(this->url)));
}

void TopicInfo::handleTopicReady(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QString response(reply->readAll());
        QJsonParseError error;
        QJsonDocument rootDoc = QJsonDocument::fromJson(response.toUtf8(), &error);

        QStandardItemModel *itemModel = new QStandardItemModel();
        QList<QStandardItem*> itemList;

        if (error.error == QJsonParseError::NoError) {
            if (rootDoc.isArray()) {
                QJsonArray array = rootDoc.array();
                foreach (QJsonValue v, array) {
                    if (v.isObject()) {
                        QJsonObject object = v.toObject();
                        Topic topic = Topic::fromJsonObject(object);

                        QStandardItem *item = new QStandardItem(QString::fromStdString(topic.title));
                        item->setData(QVariant::fromValue(topic));
                        itemList.append(item);
                    }
                }
            }
        }

        itemModel->appendColumn(itemList);
        this->listView->setModel(itemModel);

        if (autoSelectFirstItem()) {
            this->listView->setCurrentIndex(itemModel->index(0, 0));
            emit this->listView->clicked(itemModel->index(0, 0));
        }
    } else {

    }
}

void TopicInfo::setAutoSelectFirstItem(bool autoSelectFirstItem)
{
    TopicInfo::_autoSelectFirstItem = autoSelectFirstItem;
}

bool TopicInfo::autoSelectFirstItem() const
{
    return _autoSelectFirstItem;
}
