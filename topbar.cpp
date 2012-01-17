#include "topbar.hpp"

#include "settings.hpp"

#include <QtCore/QTime>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

TopBar::TopBar(const QSize &size) : QGraphicsPixmapItem(), _size(size) {
    QPixmap pix(_size);
    pix.fill(Settings::topBackroundColor());
    setPixmap(pix);
}

void TopBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    painter->setPen(Settings::foregroundColor());
    QFont f;
    f.setStyleHint(QFont::Helvetica);
    f.setPointSize(15);
    f.setWeight(QFont::DemiBold);
    painter->setFont(f);
    unsigned int w = size().width() / 15;
    painter->drawText(size().width() - w, 0, w, size().height(), Qt::AlignCenter | Qt::TextWordWrap, QTime::currentTime().toString("hh:mm"));
}
