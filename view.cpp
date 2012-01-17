#include "view.hpp"

#include "button.hpp"

#include "topbar.hpp"

#include <QtCore/QPropertyAnimation>

View::View(QGraphicsScene *parent) : QGraphicsView(parent) {
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    _topBar = new TopBar;
    _topBar->setPos(0, 0);
    scene()->addItem(_topBar);
    _cptArticles = 0;
    _actButton = NULL;
}

void View::addArticle(const Article &article) {
    Button *btn = new Button(article.draw(QRect(0, 0, 700 / 3, 700 / 3)));
    connect(btn, SIGNAL(pressed()), this, SLOT(articleClicked()));
    btn->resize(700 / 3, 700 / 3);
    btn->setPos((_cptArticles % 3) * (700 / 3), (_cptArticles / 3) * (700 / 3) + 30);
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
        animation->setStartValue(btn->geometry());
        animation->setEndValue(btn->gridGeometry());
        connect(animation, SIGNAL(finished()), btn, SLOT(setBack()));
        animation->start();
        _actButton = NULL;
    } else {
        if (_actButton != NULL && _actButton != btn) {
            delete animation;
            return;
        }
        btn->setFront();
        btn->setGridGeometry(btn->geometry());
        animation->setStartValue(btn->geometry());
        animation->setEndValue(QRectF(15, 45, 670, 670));
        animation->start();
        _actButton = btn;
    }
    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));
}
