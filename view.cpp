#include "view.hpp"

#include "button.hpp"

View::View(QGraphicsScene *parent) : QGraphicsView(parent) {
    //_topBar = new TopBar();
}

void View::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}
