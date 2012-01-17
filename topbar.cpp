#include "topbar.hpp"

#include <QtCore/QTime>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

TopBar::TopBar(const QSize &size) : QGraphicsPixmapItem(), _size(size) {
    QPixmap pix(_size);
    pix.fill(Qt::lightGray);
    setPixmap(pix);
}

void TopBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    painter->setPen(Qt::black);
    unsigned int w = size().width() / 15;
    painter->drawText(size().width() - w, 0, w, size().height(), Qt::AlignCenter | Qt::TextWordWrap, QTime::currentTime().toString("hh:mm"));
}
