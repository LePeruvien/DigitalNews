#include "topbar.hpp"

#include "settings.hpp"

#include <QtCore/QTime>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

TopBar::TopBar(const QSize &size) : QGraphicsPixmapItem(), _size(size) {
    QPixmap pix(_size);
    pix.fill(Qt::transparent);
    QPainter p(&pix);
    QPainter::RenderHints hint = p.renderHints();
    p.setPen(Settings::topBackroundColor());
    p.setBrush(Settings::topBackroundColor());
    p.setRenderHint(QPainter::Antialiasing);
    p.drawEllipse(0, 0, size.height(), size.height());
    p.drawEllipse(size.width() - size.height(), 0, size.height(), size.height());
    p.setRenderHints(hint);
    p.drawRect(0, size.height() / 2, size.width(), size.height() / 2);
    p.drawRect(size.height() / 2, 0, size.width() - size.height(), size.height() / 2);
    p.end();
    setPixmap(pix);
}

void TopBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    painter->setPen(Settings::hourColor());
    QFont f;
    f.setStyleHint(QFont::Helvetica);
    f.setPointSize(15);
    f.setWeight(QFont::DemiBold);
    painter->setFont(f);
    unsigned int w = size().width() / 15;
    painter->drawText(size().width() - w, 0, w, size().height(), Qt::AlignCenter | Qt::TextWordWrap, QTime::currentTime().toString("hh:mm"));
}
