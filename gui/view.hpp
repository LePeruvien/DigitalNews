#ifndef VIEW_HPP
#define VIEW_HPP

class Button;
class TopBar;

#include "article.hpp"

#include <QtGui/QGraphicsView>

class View : public QGraphicsView {

    Q_OBJECT

public:
    explicit View(QGraphicsScene *parent = 0, const QSize &size = QSize());

    void addArticle(const Article &article);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void articleClicked();
	void animationFinished();

private:
    TopBar*         _topBar;
    unsigned int    _cptArticles;
    Button*         _actButton;
};

#endif // VIEW_HPP
