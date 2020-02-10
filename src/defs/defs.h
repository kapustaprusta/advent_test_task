#pragma once

#include <QSize>
#include <QPoint>
#include <QColor>
#include <QString>

namespace defs
{

enum class Color
{
    BLACK = 0,
    WHITE,
    GREEN,
    YELLOW,
    BLUE
};

struct Colors
{
    Colors() = default;

    QColor white {  0,   0,   0};
    QColor black {255, 255, 255};
    QColor green {  0,  51,   0};
    QColor yellow{255, 255,  51};
    QColor blue  {  0,  51, 102};
};

struct AppSettings
{
    AppSettings() = default;

    int     cell_size    {  5};
    int     cells_counter{100};
    QString path_to_db   {"database/field.sqlite"};
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

    QString colors;

};

}