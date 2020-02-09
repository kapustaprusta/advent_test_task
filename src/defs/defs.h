#pragma once

#include <QSize>
#include <QList>
#include <QPoint>
#include <QColor>
#include <QString>

namespace defs
{

struct Colors
{
    Colors() = default;

    QColor white{  0,   0,   0};
    QColor black{255, 255, 255};
};

struct AppSettings
{
    AppSettings() = default;

    int     cell_size    {  5};
    int     cells_counter{100};
    QString path_to_db   { ""};
};

struct WindowProperties
{
    WindowProperties() = default;

    QSize  size    { 800, 600 };
    QPoint position{ 200, 200 };
};

struct FieldModel
{
    FieldModel() = default;

    int id{0};
    QList<QList<QColor>> values;

};

}