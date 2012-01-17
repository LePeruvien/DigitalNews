#include "button.hpp"

#include "settings.hpp"

#include <QtGui/QPainter>
#include <QtGui/QStyleOptionGraphicsItem>

Button::Button(const QPixmap &pixmap, QGraphicsItem *parent) : QGraphicsWidget(parent), _pix(pixmap) {
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
    _front = false;
}

QPainterPath Button::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    bool down = option->state & QStyle::State_Sunken;
    QRectF r = boundingRect();
    painter->setPen(Qt::NoPen);
    painter->setBrush(_front ? Settings::articleBackgroundColor() : Settings::foregroundColor());
    painter->drawRect(r);
    painter->setBrush(Qt::NoBrush);
    if (option->state & QStyle::State_MouseOver) {
        painter->setPen(QPen(Settings::backgroundColor(), 3));
        painter->drawRect(r);
    } else {
        painter->setPen(QPen(Settings::backgroundColor(), 1));
        painter->drawRect(r);
    }
    /*grad.setColorAt(down ? 1 : 0, Qt::darkGray);
    grad.setColorAt(down ? 0 : 1, Qt::lightGray);
    painter->setPen(Qt::NoPen);
    painter->setBrush(grad);
    if (down)
        painter->translate(2, 2);
    painter->drawRect(r.adjusted(5, 5, -5, -5));*/
    painter->drawPixmap(0, 0, _pix);
    //painter->drawPixmap(-_pix.width() / 2, -_pix.height() / 2, _pix);
}

void Button::setBack() {
    _front = false;
    setZValue(0);
}

void Button::setFront() {
    _front = true;
    setZValue(2);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *) {
    emit pressed();
    update();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
    update();
}
