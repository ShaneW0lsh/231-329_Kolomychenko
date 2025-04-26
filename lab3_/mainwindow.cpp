#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "clientinterface.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_get_1_clicked()
{
    ClientInterface *client = ClientInterface::getInstance("http://127.0.0.1:80/");

    ProcessInstance processInstance = client->getProcessInstance(1);
}


void MainWindow::on_delete_2_clicked()
{
    ClientInterface *client = ClientInterface::getInstance("http://127.0.0.1:80/");
    client->deleteProcessInstance(2);
}


void MainWindow::on_update_clicked()
{
    ClientInterface *client = ClientInterface::getInstance("http://127.0.0.1:80/");
    client->updateProcessInstance(10);
}


void MainWindow::on_create_clicked()
{
    ClientInterface *client = ClientInterface::getInstance("http://127.0.0.1:80/");
    client->createProcessInstance();
}


void MainWindow::on_get_all_clicked()
{
    ClientInterface *client = ClientInterface::getInstance("http://127.0.0.1:80/");
    client->getProcessInstances();
}

