#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QtGui/QGraphicsWidget>

class Button : public QGraphicsWidget {

    Q_OBJECT

public:
    Button(const QPixmap &pixmap, QGraphicsItem *parent = 0);

    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

signals:
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    QPixmap _pix;
};

#endif // BUTTON_HPP
