#include "view.hpp"

#include "button.hpp"
#include "settings.hpp"
#include "topbar.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
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

	poisonIvy = new IvyBinder();
	connect(poisonIvy, SIGNAL(scrollUpgesture()), this, SLOT(scrollUp()));
	connect(poisonIvy, SIGNAL(scrollDownGesture()), this, SLOT(scrollDown()));
	//connect(poisonIvy, SIGNAL(closeGesture()), this, );
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
        hideBtn(_displayed.first());
    }

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    foreach(Button* dispBtn, _displayed) {
        unsigned int col = (size().width() % (int)(dispBtn->pos().x() > 0 ? dispBtn->pos().x() : 1)) + 1;
        QPropertyAnimation *animation = new QPropertyAnimation(dispBtn, "geometry");
        animation->setDuration(500);
        animation->setEasingCurve(QEasingCurve::OutExpo);
        animation->setStartValue(dispBtn->geometry());
        if (col < 3)
            animation->setEndValue(QRect(dispBtn->pos().x() + w, dispBtn->pos().y(), w, h));
        else
            animation->setEndValue(QRect(0, dispBtn->pos().y() + h, w, h));
        group->addAnimation(animation);
    }

    QPropertyAnimation *animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    animation->setStartValue(btn->geometry());
    animation->setEndValue(QRect(0, _topBar->size().height(), w, h));
    group->addAnimation(animation);
    group->start();
    waitForSignal(group, SIGNAL(finished()));
    _displayed << btn;
}

void View::hideBtn(Button *btn) {
    QPropertyAnimation *animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    btn->setZValue(1);
    animation->setStartValue(btn->geometry());
    animation->setEndValue(QRect(size().width() + 5, btn->pos().y(), btn->size().width(), btn->size().height()));
    animation->start();
    _displayed.remove(_displayed.indexOf(btn));
}

void View::scrollDown() {
    qDebug() << _displayed.size();
    if (_displayed.size() <= 6)
        return;
    unsigned int w = size().width() / 3;
    unsigned int h = (size().height() - _topBar->size().height()) / 3;
    QVector<Button*> toHide;
    QVector<Button*> toUp;
    QVector<Button*> toAdd;
    unsigned int firstDisplayed = _btns.indexOf(_displayed.first());
    unsigned int firstToAdd = qMax((int)firstDisplayed - 3, 0);
    unsigned int lastToUp = qMin((int)6, _displayed.size());
    for (unsigned int i = 0; i < lastToUp; ++i)
        toUp << _displayed[i];
    for (unsigned int i = lastToUp; i < lastToUp + 3; ++i)
        toHide << _displayed[i];
    for (unsigned int i = firstToAdd; i < firstToAdd + 3; ++i)
         toAdd << _btns[i];

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    foreach (Button* btn, toUp) {
        QPropertyAnimation *animation = new QPropertyAnimation(btn, "geometry");
        animation->setDuration(750);
        animation->setEasingCurve(QEasingCurve::OutExpo);
        animation->setStartValue(btn->geometry());
        animation->setEndValue(QRect(btn->pos().x(), btn->pos().y() - h, btn->geometry().width(), btn->geometry().height()));
        group->addAnimation(animation);
    }

    foreach (Button* btn, toHide) {
        QPropertyAnimation *animation = new QPropertyAnimation(btn, "geometry");
        animation->setDuration(750);
        animation->setEasingCurve(QEasingCurve::OutExpo);
        animation->setStartValue(btn->geometry());
        animation->setEndValue(QRect(btn->pos().x(), -h - 2, btn->geometry().width(), btn->geometry().height()));
        group->addAnimation(animation);
        _displayed.remove(_displayed.indexOf(btn));
    }

    foreach (Button* btn, toAdd) {
        qDebug() << "displayed size : " << _displayed.size();
        unsigned int col = _displayed.size() % 3;
        _displayed << btn;
        qDebug() << "displayed size : " << _displayed.size();
        qDebug() << "col : " << col;
        btn->setPos(col * w, 3 * h + _topBar->size().height());
        qDebug() << btn->geometry();
        QPropertyAnimation *animation = new QPropertyAnimation(btn, "geometry");
        animation->setDuration(750);
        animation->setEasingCurve(QEasingCurve::OutExpo);
        animation->setStartValue(btn->geometry());
        animation->setEndValue(QRect(btn->pos().x(), 2 * h + _topBar->size().height(), btn->geometry().width(), btn->geometry().height()));
        group->addAnimation(animation);
    }

    group->start();
    waitForSignal(group, SIGNAL(finished()));
    foreach(Button* btn, toHide)
        scene()->removeItem(btn);
}

void View::scrollUp() {

}

void View::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void View::wheelEvent(QWheelEvent *event) {
    if (event->orientation() == Qt::Horizontal)
        return;
    if (event->delta() > 0)
        scrollUp();
    else
        scrollDown();
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
