#include "view.hpp"

#include "button.hpp"
#include "settings.hpp"
#include "topbar.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTimer>

#include <QtCore/QDebug>

View::View(QGraphicsScene *parent, const QSize &size) : QGraphicsView(parent) {
    resize(size);
    setBackgroundBrush(Qt::black);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    _topBar = new TopBar(QSize(size.width(), size.height() / 15));
    _topBar->setPos(0, 0);
    scene()->addItem(_topBar);
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
    btn->setPos(0, _topBar->size().height());
    scene()->addItem(btn);

    _articles << article;
    _btns << btn;
    if (_displayed.size() >= 9) {
        hideBtn(_displayed.last());
        _displayed.remove(_displayed.size() - 1);
    }

    foreach(Button* dispBtn, _displayed) {
        unsigned int col = (size().width() % (int)(dispBtn->pos().x() > 0 ? dispBtn->pos().x() : 1)) + 1;
        unsigned int row = (size().height() % (int)(dispBtn->pos().y() - _topBar->size().height() > 0 ? dispBtn->pos().y() - _topBar->size().height() : 1)) + 1;
        QPropertyAnimation *animation = new QPropertyAnimation(dispBtn, "geometry");
        animation->setDuration(500);
        animation->setEasingCurve(QEasingCurve::OutExpo);
        animation->setStartValue(dispBtn->geometry());
        if (col < 3)
            animation->setEndValue(QRect(dispBtn->pos().x() + w, dispBtn->pos().y(), w, h));
        else
            animation->setEndValue(QRect(0, dispBtn->pos().y() + h, w, h));
        animation->start();
        waitForSignal(animation, SIGNAL(finished()));
    }

    QPropertyAnimation *animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    animation->setStartValue(btn->geometry());
    animation->setEndValue(QRect(0, _topBar->size().height(), w, h));
    animation->start();
    waitForSignal(animation, SIGNAL(finished()));
    _displayed << btn;
}

void View::hideBtn(Button *btn) {
    QPropertyAnimation *animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    btn->setZValue(1);
    animation->setStartValue(btn->geometry());
    animation->setEndValue(QRect(size().width() + 5, size().height() + 5, btn->size().width(), btn->size().height()));
    animation->start();
    _displayed.remove(_displayed.indexOf(btn));
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
        btn->changePixmap(btn->getArticle().drawArticle(rect));
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

bool waitForSignal(QObject *p_obj, const char *p_sig, int p_timeout) {
    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;

    QObject::connect(p_obj, p_sig, &loop, SLOT(quit()));
    QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

    timer.start(p_timeout);
    loop.exec();

    return timer.isActive();
}
