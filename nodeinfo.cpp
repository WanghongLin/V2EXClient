#include "nodeinfo.h"

NodeInfo::NodeInfo(QObject *parent) : QObject(parent)
{

}

NodeInfo* NodeInfo::load(int nodeId)
{
    NodeInfo* nodeInfo = new NodeInfo(nodeId);
    return nodeInfo;
}

void NodeInfo::into(QWidget *widget)
{
    this->widget = widget;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNodeInfoReady(QNetworkReply*)));
    QString url = QString("https://www.v2ex.com/api/nodes/show.json?id=");
    url += QString::number(nodeId);
    QDebug(QtInfoMsg) << "load node info " << url;
    manager->get(QNetworkRequest(QUrl(url)));
}

void NodeInfo::handleNodeInfoReady(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonParseError error;
        QJsonDocument rootDoc = QJsonDocument::fromJson(reply->readAll(), &error);
        if (error.error == QJsonParseError::NoError) {
            if (rootDoc.isObject()) {
                QJsonObject object = rootDoc.object();
                Node node = Node::fromJsonObject(object);

                QDebug(QtDebugMsg) << "handleNodeInfoReady " << QString::fromStdString(node.header);

                QString toolTips = QString::fromStdString(node.name);
                toolTips.append('\n');
                toolTips += QString::fromStdString(node.header);
                toolTips.append('\n');
                toolTips.append('\n');
                toolTips += "since ";
                QDateTime dateTime = QDateTime::fromMSecsSinceEpoch((qint64)node.created * 1000);
                toolTips += dateTime.toLocalTime().toString();

                this->widget->setToolTip(toolTips);
                this->widget->setToolTipDuration(10000);
            }
        }
    } else {
        QDebug(QtDebugMsg) << reply->errorString();
    }
}
