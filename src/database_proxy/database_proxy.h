#pragma once

#include <QtSql>
#include <QString>

namespace dabase
{

class DatabaseProxy
{
public:
    explicit DatabaseProxy() = default;
            ~DatabaseProxy() = default;

    bool Init(const QString& db_type, const QString& db_url);

private:
    QSqlDatabase db_;
};

} // database