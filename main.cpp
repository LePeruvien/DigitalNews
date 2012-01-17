#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QGraphicsScene>

#include "article.hpp"
#include "button.hpp"
#include "view.hpp"


#include <QtCore/QPropertyAnimation>
#include <QtGui/QPushButton>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    const QRect screen = QApplication::desktop()->screenGeometry();
    QGraphicsScene scene(screen);

    Article article;
	article.setContent("Title", "Test d'article un peu long", Article::Economy);

    View v(&scene, screen.size());
    v.showFullScreen();

    for (unsigned int i = 0; i < 9; ++i)
        v.addArticle(article);

    return app.exec();
}
