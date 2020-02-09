#include <QMutexLocker>

#include "database_proxy.h"

namespace database
{

DatabaseProxy::DatabaseProxy()
{
    is_init_.store(false);
}

DatabaseProxy::~DatabaseProxy()
{
    db_.close();
}

bool DatabaseProxy::Init(const QString& db_type, const QString& db_url)
{
    QMutexLocker ml(&db_mutex_);

    if (db_type.isEmpty() || db_url.isEmpty())
    {
        return false;
    }

    db_ = QSqlDatabase::addDatabase(db_type);
    db_.setDatabaseName(db_url);
    is_init_.store(db_.open());

    return is_init_.load();
}

bool DatabaseProxy::Create(const defs::FieldModel& model)
{
    QMutexLocker ml(&db_mutex_);

    if (!is_init_.load())
    {
        return false;
    }

    auto query     = QSqlQuery(db_);
    auto query_str = QString("INSERT INTO field(red, green, blue) VALUES (%2, %3, %4);");

    for (const auto& color : model.colors)
    {
        const auto prepared_query_str = query_str.arg(0, 10).arg(color.red(), 10).arg(color.green(), 10).arg(color.blue(), 10);
        const auto isOk               = query.exec(prepared_query_str);

        qDebug() << prepared_query_str;

        if (!isOk)
        {
            return false;
        }
    }

    return true;
}

bool DatabaseProxy::Read(defs::FieldModel& model)
{
    QMutexLocker ml(&db_mutex_);

    auto query     = QSqlQuery(db_);
    auto query_str = QString("SELECT * FROM field;");

    qDebug() << is_init_.load();

    if (!is_init_.load() || !query.exec(query_str))
    {
        return false;
    }

    auto sql_record = query.record();
    while (query.next())
    {
        auto cell_color = QColor();
        cell_color.setRed(query.value(sql_record.indexOf("red")).toInt());
        cell_color.setGreen(query.value(sql_record.indexOf("green")).toInt());
        cell_color.setBlue(query.value(sql_record.indexOf("blue")).toInt());
        
        model.colors.append(cell_color);
    }

    return true;
}

bool DatabaseProxy::Delete()
{
    QMutexLocker ml(&db_mutex_);

    if (!is_init_.load())
    {
        return false;
    }

    auto query     = QSqlQuery(db_);
    auto query_str = QString("DELETE FROM field");

    return query.exec(query_str);
}

} // database