#include <QtGui/QApplication>
#include <QtGui/QGraphicsScene>

#include "article.hpp"
#include "button.hpp"
#include "view.hpp"


#include <QtCore/QPropertyAnimation>
#include <QtGui/QPushButton>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene(0, 0, 700, 700);

    Article article;
    article.setContent("Test d'article un peu long");

    View v(&scene);
    v.resize(700, 700);
    v.show();

    for (unsigned int i = 0; i < 9; ++i)
        v.addArticle(article);

    return app.exec();
}
