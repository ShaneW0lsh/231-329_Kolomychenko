#include "processinstance.h"

ProcessInstance::ProcessInstance(int id, QString process_name, QString state, QString update_time, QString description, int priority)
    : id(id), process_name(process_name), state(state), update_time(update_time), description(description), priority(priority) {}

ProcessInstance ProcessInstance::fromJson(const QJsonObject& json) {
    return ProcessInstance(
        json["id"].toInt(),
        json["process_name"].toString(),
        json["state"].toString(),
        json["update_time"].toString(),
        json["description"].toString(),
        json["priority"].toInt()
    );
}
