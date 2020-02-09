#pragma once

#include <QPoint>
#include <QColor>
#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

#include "../defs/defs.h"

namespace cell
{

class CellItem final : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit CellItem(const QSize& size, const QPoint& coordinates, const defs::Color& color, QObject* parent = Q_NULLPTR);
            ~CellItem() = default;

    defs::Color GetColor();
    QSize  GetSize();
    QPoint GetCoordinates();

private:
    QSize       size_;
    QPoint      coordinates_;
    defs::Color color_;

    defs::Colors colors_;

    //void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

} // cell