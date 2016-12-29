#include "memberinfo.h"

MemberInfo::MemberInfo(QObject *parent) : QObject(parent)
{

}

MemberInfo::MemberInfo(int memberId)
{
    this->memberId = memberId;
}

MemberInfo* MemberInfo::load(int memberId)
{
    MemberInfo* memberInfo = new MemberInfo(memberId);

    return memberInfo;
}

void MemberInfo::into(QWidget *widget)
{
    this->widget = widget;
    QString url = QString("https://www.v2ex.com/api/members/show.json?id=");
    url += QString::number(this->memberId);

    QDebug(QtDebugMsg) << "load member info " << url;

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleMemberInfoReady(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

void MemberInfo::handleMemberInfoReady(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll(), &error);
        if (error.error == QJsonParseError::NoError) {
            if (doc.isObject()) {
                QJsonObject object = doc.object();
                Member member = Member::fromJsonObject(object);

                QString toolTips = QString::fromStdString(member.username);
                toolTips.append('\n');
                toolTips += QString::fromStdString(member.bio);
                toolTips.append('\n');
                toolTips += "Join @ ";

                QDateTime joinTime = QDateTime::fromMSecsSinceEpoch((qint64)member.created * 1000);
                toolTips += joinTime.toLocalTime().toString();

                this->widget->setToolTip(toolTips);
                this->widget->setToolTipDuration(10000);
            }
        } else {
            QDebug(QtDebugMsg) << error.errorString();
        }
    } else {
        QDebug(QtDebugMsg) << reply->errorString();
    }
}
