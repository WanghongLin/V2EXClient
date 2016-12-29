#ifndef V2EXWINDOW_H
#define V2EXWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QList>

// handle json data
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "v2ex.h"
#include "topicinfo.h"

namespace Ui {
class V2EXWindow;
}

class V2EXWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit V2EXWindow(QWidget *parent = 0);
    ~V2EXWindow();

    void handleTopicClicked(const QModelIndex &index);
    void handleTopicDoubleClicked(const QModelIndex &index);

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_latestListView_clicked(const QModelIndex &index);

    void on_latestListView_doubleClicked(const QModelIndex &index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::V2EXWindow *ui;
    TopicInfo* hotTopics;
    TopicInfo* latestTopics;
};

#endif // V2EXWINDOW_H
