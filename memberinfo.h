#ifndef MEMBERINFO_H
#define MEMBERINFO_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDateTime>
#include <QTimeZone>
#include "v2ex.h"

class MemberInfo : public QObject
{
    Q_OBJECT
public:
    explicit MemberInfo(QObject *parent = 0);

    MemberInfo(int memberId);
    ~MemberInfo() {

    }

    static MemberInfo* load(int memberId);
    void into(QWidget* widget);
signals:

public slots:
    void handleMemberInfoReady(QNetworkReply *reply);

private:
    int memberId;
    QWidget* widget;
};

#endif // MEMBERINFO_H
