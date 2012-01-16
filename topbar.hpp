#ifndef TOPBAR_HPP
#define TOPBAR_HPP

#include <QtGui/QGraphicsPixmapItem>

class TopBar : public QGraphicsPixmapItem {
public:
    explicit TopBar();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TOPBAR_HPP
