#include "clientinterface.h"
#include <QObject>

ClientInterface* ClientInterface::existing_object = nullptr;

ProcessInstance ClientInterface::getProcessInstance(const unsigned int id)
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://127.0.0.1:80/processInstance/" + QString::number(id)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_client->get(request);

    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray responseData = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    QList<ProcessInstance> processInstances = deserializeJson(jsonDoc);

    qDebug() << "Получено процессов:" << processInstances.size();
    for (const ProcessInstance &processInstance : processInstances) {
        qDebug() << "id:" << processInstance.id << "| Process name:" << processInstance.process_name
                 << "| State:" << processInstance.state << "| Update time:" << processInstance.update_time
                 << "| Description:" << processInstance.description << "| Priority:" << processInstance.priority;
    }

    reply->deleteLater();

    return processInstances.isEmpty() ? ProcessInstance() : processInstances.first();
}

QList<ProcessInstance> ClientInterface::deserializeJson(const QJsonDocument& jsonDoc)
{
    QList<ProcessInstance> processInstances = QList<ProcessInstance>();

    if (jsonDoc.isArray()) {
        QJsonArray jsonArray = jsonDoc.array();
        for (const QJsonValue &value : jsonArray) {
            if (value.isObject()) {
                processInstances.append(ProcessInstance::fromJson(value.toObject()));
            }
        }
    } else if (jsonDoc.isObject()) {
        processInstances.append(ProcessInstance::fromJson(jsonDoc.object()));
    } else {
        qDebug() << "Ошибка: Ожидался JSON-объект или массив!";
    }

    return processInstances;
}


void ClientInterface::deleteProcessInstance(const unsigned int id)
{
    QUrl url("http://127.0.0.1:80/processInstance/" + QString::number(id));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_client->deleteResource(request);

    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Процесс успешно удален. ID:" << id;
    } else {
        qDebug() << "Ошибка при удалении процесса:" << reply->errorString();
    }
    reply->deleteLater();
}

void ClientInterface::updateProcessInstance(const unsigned int id)
{
    QJsonObject json;
    json["process_name"] = "Updated QT Process Instance";
    json["state"] = "UPDATED";
    json["update_time"] = "2025-02-20 18:56:00+05";
    json["description"] = "A Process Instance updated by QT!";
    json["priority"] = 10;


    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QUrl url("http://127.0.0.1:80/processInstance/" + QString::number(id));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_client->sendCustomRequest(request, "PATCH", data);

    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Процесс успешно обновлен!";
        qDebug() << "Ответ сервера:" << reply->readAll();
    } else {
        qDebug() << "Ошибка при обновлении процесса:" << reply->errorString();
    }

    reply->deleteLater();
}


void ClientInterface::createProcessInstance()
{
    QJsonObject json;
    json["process_name"] = "QT Process Instance";
    json["state"] = "SUSPENDED";
    json["update_time"] = "2025-02-20 18:56:00+05";
    json["description"] = "A Process Instance created by QT!";
    json["priority"] = 5;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QUrl url("http://127.0.0.1:80/processInstance");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_client->post(request, data);

    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Процесс успешно создан";
        qDebug() << "Ответ сервера:" << reply->readAll();
    } else {
        qDebug() << "Ошибка при создании процесса:" << reply->errorString();
    }

    reply->deleteLater();
}

void ClientInterface::getProcessInstances()
{
    QNetworkRequest request; ;
    request.setUrl(QUrl("http://127.0.0.1:80/processInstance"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_client->get(request);


    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QByteArray responseData = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    QList<ProcessInstance> processInstances = deserializeJson(jsonDoc);

    qDebug() << "Получено процессов:" << processInstances.size();
    for (const ProcessInstance &processInstance : processInstances) {
        qDebug() << "id:" << processInstance.id << "| Process name:" << processInstance.process_name
                 << "| State:" << processInstance.state << "| Update time:" << processInstance.update_time
                 << "| Description:" << processInstance.description << "| Priority:" << processInstance.priority;
    }
    reply->deleteLater();
}
