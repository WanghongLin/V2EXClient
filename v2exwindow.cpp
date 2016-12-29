#include "v2exwindow.h"
#include "ui_v2exwindow.h"
#include "v2ex.h"
#include "networkimage.h"
#include "nodeinfo.h"
#include "memberinfo.h"
#include "topicinfo.h"

#include <QStringListModel>
#include <QStringList>
#include <QStringListModel>

#include <QDateTime>
#include <QColor>
#include <QPalette>

V2EXWindow::V2EXWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::V2EXWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(QSize(800, 600));

    ui->listView->setFlow(QListView::TopToBottom);
    ui->listView->setLayoutMode(QListView::SinglePass);

    QStringList list;
    list << "Hello 1" << "hello 2" << "hello 3";
    QStringListModel *model = new QStringListModel();
    model->setStringList(list);
    ui->listView->setModel(model);

    hotTopics = TopicInfo::load(QString("https://www.v2ex.com/api/topics/hot.json"));
    hotTopics->setAutoSelectFirstItem(true);
    hotTopics->into(ui->listView);

    latestTopics = TopicInfo::load(QString("https://www.v2ex.com/api/topics/latest.json"));
    latestTopics->setAutoSelectFirstItem(false);
    latestTopics->into(ui->latestListView);
}

V2EXWindow::~V2EXWindow()
{
    delete hotTopics;
    delete latestTopics;
    delete ui;
}

void V2EXWindow::on_listView_clicked(const QModelIndex &index)
{
    this->handleTopicClicked(index);
}

void V2EXWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    this->handleTopicDoubleClicked(index);
}

void V2EXWindow::on_latestListView_clicked(const QModelIndex &index)
{
    this->handleTopicClicked(index);
}

void V2EXWindow::on_latestListView_doubleClicked(const QModelIndex &index)
{
    this->handleTopicDoubleClicked(index);
}

void V2EXWindow::handleTopicClicked(const QModelIndex &index)
{
    Topic topic = index.data(Qt::UserRole + 1).value<Topic>();

    ui->titleLabel->setText(index.data().toString());

    // author
    ui->authorLabel->setText(QString::fromStdString(topic.member.username));
    MemberInfo::load(topic.member.id)->into(ui->authorLabel);

    // node
    ui->nodeLabel->setText(QString("@") + QString::fromStdString(topic.node.name));
    NodeInfo::load(topic.node.id)->into(ui->nodeLabel);

    // time
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(topic.created * 1000);
    ui->timeLabel->setText(dateTime.toLocalTime().toString());

    // content
    QPalette p = ui->contentTextEdit->palette();
    p.setColor(QPalette::Base, QColor(0, 0, 0, 0));
    ui->contentTextEdit->setPalette(p);
    ui->contentTextEdit->setText(QString::fromStdString(topic.content));

    // avatar
    NetworkImage::load(QString::fromStdString(topic.member.avatar_normal))
            ->into(ui->avatarImageView);
}

void V2EXWindow::handleTopicDoubleClicked(const QModelIndex &index)
{
    Topic topic = index.data(Qt::UserRole + 1).value<Topic>();
    QDebug(QtDebugMsg) << "doubleClicked " << topic.url.c_str();
}

void V2EXWindow::on_tabWidget_currentChanged(int index)
{
    QDebug(QtDebugMsg) << "tab changed " << index;
    QModelIndex modelIndex;
    switch (index) {
    case 0:
        modelIndex = ui->listView->model()->index(0, 0);
        ui->listView->setCurrentIndex(modelIndex);
        this->handleTopicClicked(modelIndex);
        break;
    case 1:
        modelIndex = ui->latestListView->model()->index(0, 0);
        ui->latestListView->setCurrentIndex(modelIndex);
        this->handleTopicClicked(modelIndex);
        break;
    default:
        break;
    }
}
