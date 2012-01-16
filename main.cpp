#include <QtGui/QApplication>
#include <QtGui/QGraphicsScene>

#include "article.hpp"
#include "button.hpp"
#include "view.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene(0, 0, 700, 700);

    Article article;
    article.setContent("Test d'article un peu long");

    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            Button *btn = new Button(article.draw(QRect(0, 0, 700 / 3, 700 / 3)));
            btn->resize(700 / 3, 700 / 3);
            btn->setPos(i * (700 / 3), j * (700 / 3));
            scene.addItem(btn);
        }
    }

    View v(&scene);
    v.resize(700, 700);
    v.show();

    return app.exec();
}
