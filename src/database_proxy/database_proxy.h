#pragma once

#include <QtSql>
#include <QMutex>

#include "../defs/defs.h"

namespace database
{

class DatabaseProxy
{
public:
    explicit DatabaseProxy();
    ~DatabaseProxy();

    bool Init(const QString& db_type, const QString& db_url);

    bool Create(const defs::FieldModel& model);
    bool Read(defs::FieldModel& model);
    bool Delete();

private:
    std::atomic_bool is_init_;

    QMutex db_mutex_;
    QSqlDatabase db_;
};

} // database