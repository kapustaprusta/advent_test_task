#include "database_proxy.h"

namespace database
{

bool DatabaseProxy::Init(const QString& db_type, const QString& db_url)
{
    if (db_type.isEmpty() || db_url.isEmpty())
    {
        return false;
    }

    db_ = QSqlDatabase::addDatabase(db_type);
    db_.setDatabaseName(db_url);

    return db_.open();
}

} // database