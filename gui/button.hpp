#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QtGui/QGraphicsWidget>

#include "article.hpp"

class Button : public QGraphicsWidget {

    Q_OBJECT

public:
	Button(const QPixmap &pixmap, const Article &article, QGraphicsItem *parent = 0);

    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

    inline bool isFront() const {
        return _front;
    }

    inline QRectF gridGeometry() const {
        return _gridGeometry;
    }

    inline void setGridGeometry(const QRectF &geometry) {
        _gridGeometry = geometry;
    }

	inline Article getArticle() const {
		return _article;
	}

	void changePixmap(const QPixmap &pixmap);

public slots:
    void setBack();
    void setFront();

signals:
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    QPixmap _pix;
    bool    _front;
    QRectF  _gridGeometry;
	Article _article;
};

#endif // BUTTON_HPP
