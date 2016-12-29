

#include "v2ex.h"

Topic Topic::fromJsonObject(QJsonObject& object)
{
    Topic topic;

    for (QJsonObject::ConstIterator i = object.constBegin();
         i != object.constEnd(); i++) {
        if (i.key() == "node" && i.value().isObject()) {
            QJsonObject nodeObject = i.value().toObject();
            topic.node = Node::fromJsonObject(nodeObject);
        }

        if (i.key() == "member" && i.value().isObject()) {
            QJsonObject memberObject = i.value().toObject();
            topic.member = Member::fromJsonObject(memberObject);
        }
    }

    topic.id = object.value("id").toInt();
    topic.content = object.value("content").toString().toStdString();
    topic.content_rendered = object.value("content_rendered").toString().toStdString();
    topic.created = object.value("created").toInt();
    topic.last_modified = object.value("last_modified").toInt();
    topic.last_touched = object.value("last_touched").toInt();
    topic.replies = object.value("replies").toInt();
    topic.title = object.value("title").toString().toStdString();
    topic.url = object.value("url").toString().toStdString();

    return topic;
}

Node Node::fromJsonObject(QJsonObject& object)
{

    Node node;

    node.avatar_large = object.value("avatar_large").toString().toStdString();
    node.avatar_mini = object.value("avatar_mini").toString().toStdString();
    node.avatar_normal = object.value("avatar_normal").toString().toStdString();
    node.id = object.value("id").toInt();
    node.name = object.value("name").toString().toStdString();
    node.title = object.value("title").toString().toStdString();
    node.title_alternative = object.value("title_alternative").toString().toStdString();
    node.topics = object.value("topics").toInt();
    node.url = object.value("url").toString().toStdString();

    if (!object.value("stars").isNull()) {
        node.stars = object.value("stars").toInt();
    }
    if (!object.value("header").isNull()) {
        node.header = object.value("header").toString().toStdString();
    }
    if (!object.value("footer").isNull()) {
        node.footer = object.value("footer").toString().toStdString();
    }
    if (!object.value("created").isNull()) {
        node.created = object.value("created").toInt();
    }

    return node;
}

Member Member::fromJsonObject(QJsonObject& object)
{
    Member member;

    member.avatar_large = object.value("avatar_large").toString().toStdString();
    member.avatar_mini = object.value("avatar_mini").toString().toStdString();
    member.avatar_normal = object.value("avatar_normal").toString().toStdString();
    member.id = object.value("id").toInt();
    member.tagline = object.value("tagline").toString().toStdString();
    member.username = object.value("username").toString().toStdString();

    if (!object.value("status").isNull()) {
        member.status = object.value("status").toString().toStdString();
    }
    if (!object.value("website").isNull()) {
        member.website = object.value("website").toString().toStdString();
    }
    if (!object.value("twitter").isNull()) {
        member.twitter = object.value("twitter").toString().toStdString();
    }
    if (!object.value("psn").isNull()) {
        member.psn = object.value("psn").toString().toStdString();
    }
    if (!object.value("github").isNull()) {
        member.github = object.value("github").toString().toStdString();
    }
    if (!object.value("btc").isNull()) {
        member.btc = object.value("btc").toString().toStdString();
    }
    if (!object.value("location").isNull()) {
        member.location = object.value("location").toString().toStdString();
    }
    if (!object.value("bio").isNull()) {
        member.bio = object.value("bio").toString().toStdString();
    }
    if (!object.value("created").isNull()) {
        member.created = object.value("created").toInt();
    }

    return member;
}
