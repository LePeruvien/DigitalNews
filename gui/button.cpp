#include "button.hpp"

#include "settings.hpp"

#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtGui/QStyleOptionGraphicsItem>

Button::Button(const QPixmap &pixmap, const Article &article, QGraphicsItem *parent) : QGraphicsWidget(parent), _pix(pixmap), _article(article) {
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
    QRectF r = boundingRect();
    painter->setPen(Qt::NoPen);
    painter->setBrush(_front ? Settings::articleBackgroundColor() : Settings::backroundButton());
    painter->drawRect(r);
    painter->setBrush(Qt::NoBrush);
    if (option->state & QStyle::State_MouseOver) {
        if (_front) {
            painter->setPen(QPen(Settings::topBackroundColor(), 3));
            painter->drawRect(r);
        } else {
            QPixmap background(":/gui/Article_Selection");
            painter->drawPixmap(r.toRect(), background);
        }
    } else {
        painter->setPen(QPen(Settings::topBackroundColor(), 1));
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

void Button::changePixmap(const QPixmap &pixmap) {
	_pix = pixmap;
}
