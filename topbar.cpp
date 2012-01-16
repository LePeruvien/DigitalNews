#include "topbar.hpp"

#include <QtGui/QPixmap>

TopBar::TopBar() : QGraphicsPixmapItem() {
    QPixmap pix(700, 30);
    pix.fill(Qt::red);
    setPixmap(pix);
}

void TopBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
}
