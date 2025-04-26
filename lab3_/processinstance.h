#ifndef PROCESSINSTANCE_H
#define PROCESSINSTANCE_H

#include <QString>
#include <QJsonObject>

class ProcessInstance
{
public:
    int id;
    QString process_name;
    QString state;
    QString update_time;
    QString description;
    int priority;

    ProcessInstance(int id, QString process_name, QString state, QString update_time, QString description, int priority);

    ProcessInstance()
        : id(0), process_name(""), update_time(""), description(""), priority(0) {}

    static ProcessInstance fromJson(const QJsonObject &json);
};

#endif // PROCESSINSTANCE_H
