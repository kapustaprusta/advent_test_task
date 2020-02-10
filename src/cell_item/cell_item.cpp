#include <QGraphicsSceneMouseEvent>

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
    return {0, 0, qreal(size_.width()), qreal(size_.height())};
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
        case defs::Color::GREEN:
            painter->setBrush(colors_.green);
            break;
        case defs::Color::YELLOW:
            painter->setBrush(colors_.yellow);
            break;
        case defs::Color::BLUE:
            painter->setBrush(colors_.blue);
            break;
    }
    
    painter->drawRect(0, 0, size_.width(), size_.height());
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        color_ = defs::Color::YELLOW;
    }
    else if (event->button() == Qt::LeftButton)
    {
        color_ = defs::Color::GREEN;
    }

    update();
    QGraphicsItem::mousePressEvent(event);
}

defs::Color CellItem::GetColor() const
{
    return color_;
}

QSize CellItem::GetSize() const
{
    return size_;
}

QPoint CellItem::GetCoordinates() const
{
    return coordinates_;
}

} // cell