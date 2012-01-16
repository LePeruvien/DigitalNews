#ifndef VIEW_HPP
#define VIEW_HPP

class TopBar;

#include <QtGui/QGraphicsView>

class View : public QGraphicsView {
    Q_OBJECT
public:
    explicit View(QGraphicsScene *parent = 0);
    
protected:
     void resizeEvent(QResizeEvent *event);

private:
     //TopBar* _topBar;
};

#endif // VIEW_HPP
