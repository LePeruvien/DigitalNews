#ifndef TOPBAR_HPP
#define TOPBAR_HPP

#include <QtGui/QGraphicsPixmapItem>

class TopBar : public QGraphicsPixmapItem {
public:
    explicit TopBar(const QSize &size);

    inline QSize size() const {
        return _size;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QSize _size;
};

#endif // TOPBAR_HPP
