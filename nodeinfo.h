#ifndef NODEINFO_H
#define NODEINFO_H

#include <QObject>
#include <QWidget>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDateTime>
#include <QTimeZone>
#include <QDebug>
#include "v2ex.h"

class NodeInfo : public QObject
{
    Q_OBJECT
public:
    explicit NodeInfo(QObject *parent = 0);

    NodeInfo(int nodeId) {
        this->nodeId = nodeId;
    }

    static NodeInfo* load(int nodeId);
    void into(QWidget* widget);

signals:

public slots:
    void handleNodeInfoReady(QNetworkReply *reply);

private:
    int nodeId;
    QWidget* widget;
};

#endif // NODEINFO_H
