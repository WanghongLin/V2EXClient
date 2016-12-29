#ifndef TOPICINFO_H
#define TOPICINFO_H

#include <QObject>
#include <QList>
#include <QListView>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include <QStandardItem>
#include <QStandardItemModel>

#include "v2ex.h"

class TopicInfo : public QObject
{
    Q_OBJECT
public:
    explicit TopicInfo(QObject *parent = 0);
    TopicInfo(QString url) {
        this->url = url;
    }

    static TopicInfo* load(QString url);
    void setAutoSelectFirstItem(bool autoSelectFirstItem);
    void into(QListView* listView);
    bool autoSelectFirstItem() const;
signals:

public slots:
    void handleTopicReady(QNetworkReply *reply);

private:
    QString url;
    QListView* listView;
    bool _autoSelectFirstItem;
};

#endif // TOPICINFO_H
