#ifndef V2EX
#define V2EX

#include <string>
#include <QJsonObject>
#include <QVariant>

using namespace std;

class Node
{
public:
    Node() {}
    Node(const Node& node) {
        id = node.id;
        name = node.name;
        title = node.title;
        title_alternative = node.title_alternative;
        url = node.url;
        topics = node.topics;
        avatar_mini = node.avatar_mini;
        avatar_normal = node.avatar_normal;
        avatar_large = node.avatar_large;
    }

    static Node fromJsonObject(QJsonObject& object);
    int id;
    string name;
    string title;
    string title_alternative;
    string url;
    int topics;
    string avatar_mini;
    string avatar_normal;
    string avatar_large;

    int stars;
    string header;
    string footer;
    int created;
};

class Member
{
public:
    Member() {}
    Member(const Member& member) {
        id = member.id;
        username = member.username;
        tagline = member.tagline;
        avatar_mini = member.avatar_mini;
        avatar_normal = member.avatar_normal;
        avatar_large = member.avatar_large;
    }

    static Member fromJsonObject(QJsonObject& object);
    int id;
    string username;
    string tagline;
    string avatar_mini;
    string avatar_normal;
    string avatar_large;

    string status;
    string url;
    string website;
    string twitter;
    string psn;
    string github;
    string btc;
    string location;
    string bio;
    int created;
};

class Topic
{
public:
    Topic() {}
    Topic(const Topic& topic) {
        id = topic.id;
        url = topic.url;
        content = topic.content;
        content_rendered = topic.content_rendered;
        replies = topic.replies;
        member = topic.member;
        node = topic.node;
        created = topic.created;
        last_modified = topic.last_modified;
        last_touched = topic.last_touched;
    }

    static Topic fromJsonObject(QJsonObject& object);
    int id;
    string title;
    string url;
    string content;
    string content_rendered;
    int replies;
    Member member;
    Node node;
    long created;
    long last_modified;
    long last_touched;
};

Q_DECLARE_METATYPE(Member);

Q_DECLARE_METATYPE(Node) ;

Q_DECLARE_METATYPE(Topic);

#endif // V2EX
