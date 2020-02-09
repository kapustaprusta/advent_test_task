#include "cell_item.h"

namespace cell
{

CellItem::CellItem(const QSize& size, const QPoint& coordinates, const defs::Color& color, QObject* parent)
    : QObject(parent)
{
    size_        = size;
    color_       = color;
    coordinates_ = coordinates;
    colors_      = defs::Colors{};
}

QRectF CellItem::boundingRect() const
{
    return QRectF(0, 0, size_.width(), size_.height());
}

void CellItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    switch (color_)
    {
        case defs::Color::BLACK:
            painter->setBrush(colors_.black);
            break;
        case defs::Color::WHITE:
            painter->setBrush(colors_.white);
            break;
    }
    
    painter->drawRect(0, 0, size_.width(), size_.height());
}

defs::Color CellItem::GetColor()
{
    return color_;
}

QSize CellItem::GetSize()
{
    return size_;
}

QPoint CellItem::GetCoordinates()
{
    return coordinates_;
}

} // cell