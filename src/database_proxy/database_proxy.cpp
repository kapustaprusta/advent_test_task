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

    if (db_type.isEmpty() || db_url.isEmpty() || is_init_.load())
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
    const auto query_str = QString("INSERT INTO field(id, colors) VALUES (%1, '%2');");

    const auto prepared_query_str = query_str.arg(QString::number(0)).arg(model.colors);
    const auto is_ok              = query.exec(prepared_query_str);

    return is_ok;
}

bool DatabaseProxy::Read(defs::FieldModel& model)
{
    QMutexLocker ml(&db_mutex_);

          auto query     = QSqlQuery(db_);
    const auto query_str = QString("SELECT * FROM field;");

    if (!is_init_.load() || !query.exec(query_str))
    {
        return false;
    }

    const auto sql_record = query.record();
    if (query.next())
    {
        model.colors = query.value(sql_record.indexOf("colors")).toString();
    }

    return !sql_record.isEmpty();
}

bool DatabaseProxy::Delete()
{
    QMutexLocker ml(&db_mutex_);

    if (!is_init_.load())
    {
        return false;
    }

          auto query     = QSqlQuery(db_);
    const auto query_str = QString("DELETE FROM field");

    return query.exec(query_str);
}

} // database