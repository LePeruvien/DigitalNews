#include "topbar.hpp"

#include <QtCore/QTime>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

TopBar::TopBar() : QGraphicsPixmapItem() {
    QPixmap pix(700, 30);
    pix.fill(Qt::lightGray);
    setPixmap(pix);
}

void TopBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    painter->setPen(Qt::black);
    painter->drawText(650, 0, 50, 30, Qt::AlignCenter | Qt::TextWordWrap, QTime::currentTime().toString("hh:mm"));
}
