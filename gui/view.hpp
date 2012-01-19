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
    void hideBtn(Button* btn);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void articleClicked();
	void animationFinished();

private:
    TopBar*             _topBar;
    unsigned int        _cptArticles;
    Button*             _actButton;
    QVector<Button*>    _btns;
    QVector<Button*>    _displayed;
    QVector<Article>    _articles;
};

static bool waitForSignal(QObject *, const char *, int = 5000);

#endif // VIEW_HPP
