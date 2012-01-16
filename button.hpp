#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QtGui/QGraphicsWidget>

class Button : public QGraphicsWidget {

    Q_OBJECT

public:
    Button(const QPixmap &pixmap, QGraphicsItem *parent = 0);

    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    inline bool isFront() const {
        return _front;
    }

    inline void setFront(bool front) {
        _front = front;
    }

    inline QRectF gridGeometry() const {
        return _gridGeometry;
    }

    inline void setGridGeometry(const QRectF &geometry) {
        _gridGeometry = geometry;
    }

signals:
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    QPixmap _pix;
    bool    _front;
    QRectF  _gridGeometry;
};

#endif // BUTTON_HPP
