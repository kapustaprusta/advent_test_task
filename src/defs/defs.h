#pragma once

#include <QSize>
#include <QPoint>
#include <QColor>
#include <QString>

namespace defs
{

enum class CellType
{
    START = 0,
    FINISH,
    ROUTE,
    DEFAULT
};

inline QString ConvertCellTypeToStr(const CellType& type)
{
    switch (type)
    {
        case CellType::START:
            return "START";
        case CellType::FINISH:
            return "FINISH";
        case  CellType::ROUTE:
            return "ROUTE";
        case CellType::DEFAULT:
        default:
            return "DEFAULT";
    }
}

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
    QColor green {  0, 255,   0};
    QColor yellow{255, 255,  51};
    QColor blue  {  0,   0, 255};

    QColor GetColor(const Color& color) const
    {
        switch (color)
        {
            case Color::BLACK:
                return black;
            case Color::BLUE:
                return blue;
            case Color::GREEN:
                return green;
            case Color::YELLOW:
                return yellow;
            case Color::WHITE:
            default:
                return white;
        }
    }
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

} // defs