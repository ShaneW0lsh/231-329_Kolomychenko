#ifndef ARTICLE_H
#define ARTICLE_H

#include <QString>
#include <QJsonObject>

class Article
{
public:
    QString title;
    QString full_text;
    QString date;
    QString author;
    bool is_publish;

    Article(QString title, QString full_text, QString date, QString author, bool is_publish);

    Article()
        : title(""), full_text(""), date(""), author(""), is_publish(false) {}

    static Article fromJson(const QJsonObject &json);

};

#endif // ARTICLE_H
