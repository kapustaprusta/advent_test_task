#pragma once

#include <QPoint>
#include <QColor>
#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

namespace cell
{

class CellItem final : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit CellItem(const QSize& size, const QPoint& coordinates, const QColor& color, QObject* parent = Q_NULLPTR);
            ~CellItem() = default;

private:
    QSize  size_;
    QColor color_;
    QPoint coordinates_;

    //void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};

} // cell