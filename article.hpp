#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include <QtGui/QPixmap>

class Article {
public:
    Article();

    void setContent(const QString &text);

    QPixmap draw(const QRect &size) const;

private:
    QString _text;
};

#endif // ARTICLE_HPP
