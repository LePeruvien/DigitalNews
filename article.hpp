#ifndef ARTICLE_HPP
#define ARTICLE_HPP

#include <QtGui/QPixmap>

class QPixmap;

class Article {
public:
    Article();

	enum Topic {
		News,
		Sport,
		Adverts,
		Economy,
		Culture
	};

	void setContent(const QString &title, const QString &text, Topic topic);
    void setContent(const QString &text);

    QPixmap draw(const QRect &size) const;

private:
	QString _title;
    QString _text;
	QPixmap *_icon;
};

#endif // ARTICLE_HPP
