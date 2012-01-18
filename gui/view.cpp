#include "view.hpp"

#include "button.hpp"

#include "topbar.hpp"

#include <QtCore/QPropertyAnimation>

#include <QtCore/QDebug>

#include "settings.hpp"

View::View(QGraphicsScene *parent, const QSize &size) : QGraphicsView(parent) {
    resize(size);
    setBackgroundBrush(Qt::black);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    _topBar = new TopBar(QSize(size.width(), size.height() / 15));
    _topBar->setPos(0, 0);
    scene()->addItem(_topBar);
    _cptArticles = 0;
    _actButton = NULL;
    QPen p(Settings::topBackroundColor());
    p.setWidth(3);
    scene()->addRect(0, size.height() / 15, size.width(), size.height() / 15 * 14, p, Qt::lightGray);
}

void View::addArticle(const Article &article) {
    unsigned int w = size().width() / 3;
    unsigned int h = (size().height() - _topBar->size().height()) / 3;
	Button *btn = new Button(article.drawPreview(QRect(0, 0, w, h)), article);
    connect(btn, SIGNAL(pressed()), this, SLOT(articleClicked()));
    btn->resize(w, h);
    btn->setPos((_cptArticles % 3) * (w), (_cptArticles / 3) * h + _topBar->size().height());
    scene()->addItem(btn);
    ++_cptArticles;
}

void View::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void View::articleClicked() {
    Button *btn = dynamic_cast<Button*>(sender());
    if (!btn)
        return;

    QPropertyAnimation *animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(750);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    if (btn->isFront()) {
        btn->setZValue(1);

		unsigned int w = size().width() / 3;
		unsigned int h = (size().height() - _topBar->size().height()) / 3;
		QRect rect = QRect(0, 0, w, h);
		btn->changePixmap(btn->getArticle().drawPreview(rect));
		btn->update(rect);

        animation->setStartValue(btn->geometry());
        animation->setEndValue(btn->gridGeometry());
        connect(animation, SIGNAL(finished()), btn, SLOT(setBack()));
        animation->start();
		//_actButton = NULL;
    } else {
        if (_actButton != NULL && _actButton != btn) {
            delete animation;
            return;
        }
        btn->setFront();
        btn->setGridGeometry(btn->geometry());
        animation->setStartValue(btn->geometry());
        unsigned int w = size().width() / 17;
        unsigned int h = (size().height() - _topBar->size().height()) / 15;
		QRect rect = QRect(0, 0, 15 * w, 13 * h);
		btn->changePixmap(btn->getArticle().draw(rect));
		btn->update(rect);
		animation->setEndValue(QRectF(w, h + _topBar->size().height(), 15 * w, 13 * h));
        animation->start();
        _actButton = btn;
    }
	btn->setEnabled(false);
    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));
	connect(animation, SIGNAL(finished()), this, SLOT(animationFinished()));
}

void View::animationFinished() {
	_actButton->setEnabled(true);
	if (!_actButton->isFront())
		_actButton = NULL;
}
