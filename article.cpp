#include "article.hpp"

#include <QtGui/QPainter>

Article::Article() {
}

void Article::setContent(const QString &text) {
    _text = text;
}

QPixmap Article::draw(const QRect &size) const {
    QPixmap res(size.width(), size.height());
    res.fill(Qt::transparent);
    QPainter draw(&res);
    draw.setPen(Qt::black);
    draw.drawText(size, Qt::AlignCenter | Qt::TextWordWrap, _text);
    draw.end();
    return res;
}
