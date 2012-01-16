#include "view.hpp"

#include "button.hpp"

View::View(QGraphicsScene *parent) : QGraphicsView(parent) {
    //_topBar = new TopBar();
    _cptArticles = 0;
}

void View::addArticle(const Article &article) {
    Button *btn = new Button(article.draw(QRect(0, 0, 700 / 3, 700 / 3)));
    btn->resize(700 / 3, 700 / 3);
    btn->setPos((_cptArticles % 3) * (700 / 3), (_cptArticles / 3) * (700 / 3));
    scene()->addItem(btn);
    ++_cptArticles;
}
