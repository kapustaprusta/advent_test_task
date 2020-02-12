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
    type_        = defs::CellType::DEFAULT;
}

QRectF CellItem::boundingRect() const
{
    return {0, 0, qreal(size_.width()), qreal(size_.height())};
}

void CellItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    auto color = QColor();
    switch (type_)
    {
        case defs::CellType::START:
            color = colors_.GetColor(defs::Color::GREEN);
            break;
        case defs::CellType::FINISH:
            color = colors_.GetColor(defs::Color::YELLOW);
            break;
        case defs::CellType::ROUTE:
            color = colors_.GetColor(defs::Color::BLUE);
            break;
        case defs::CellType::DEFAULT:
        default:
            color = colors_.GetColor(color_);
            break;
    }

    painter->setBrush(color);
    painter->drawRect(0, 0, size_.width(), size_.height());
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        type_ = defs::CellType::FINISH;
    }
    else if (event->button() == Qt::LeftButton)
    {
        type_ = defs::CellType::START;
    }

    SendMetadata(type_, coordinates_);

    update();
    QGraphicsItem::mousePressEvent(event);
}

void CellItem::Reset()
{
    type_ = defs::CellType::DEFAULT;
    update();
}

void CellItem::SetType(const defs::CellType& type)
{
    type_ = type;
    update();
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