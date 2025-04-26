#include "article.h"

// Конструктор
Article::Article(QString title, QString full_text, QString date, QString author, bool is_publish)
    : title(title), full_text(full_text), date(date), author(author), is_publish(is_publish) {}

// Метод десериализации JSON → C++ объект
Article Article::fromJson(const QJsonObject &json)
{
    return Article(
        json["title"].toString(),
        json["full_text"].toString(),
        json["date"].toString(),
        json["author"].toString(),
        json["is_publish"].toBool()
        );
}
