#include "cell_item.h"

namespace cell
{

CellItem::CellItem(const QSize& size, const QPoint& coordinates, const QColor& color, QObject* parent)
    : QObject(parent)
{
    size_        = size;
    color_       = color;
    coordinates_ = coordinates;
}

QRectF CellItem::boundingRect() const
{
    return QRectF(0, 0, size_.width(), size_.height());
}

void CellItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setBrush(color_);
    painter->drawRect(0, 0, size_.width(), size_.height());
}

} // cell