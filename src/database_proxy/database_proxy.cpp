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

    if (db_.isOpen())
    {
        db_.close();
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
    auto query_str = QString("INSERT INTO field(id, values) VALUES (%1, %2);");

    QString values;
    for (const auto& color : model.colors)
    {
        values.append(QString::number(int(color)));
    }

    const auto prepared_query_str = query_str.arg(QString::number(0)).arg(values);
    const auto isOk = query.exec(prepared_query_str);

    qDebug() << prepared_query_str;

    return isOk;
}

bool DatabaseProxy::Read(defs::FieldModel& model)
{
    QMutexLocker ml(&db_mutex_);

    auto query     = QSqlQuery(db_);
    auto query_str = QString("SELECT * FROM field;");

    if (!is_init_.load() || !query.exec(query_str))
    {
        return false;
    }

    auto sql_record = query.record();
    while (query.next())
    {
        qDebug() << query.value(sql_record.indexOf("values")).toString();
    }

    return query.size() > 0;
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