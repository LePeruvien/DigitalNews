#include "article.hpp"

#include <QtGui/QPainter>

Article::Article() {
}

void Article::setContent(const QString &title, const QString &text, Topic topic) {
	_title = title;
	_text = text;

	if (topic == News)
		_icon = new QPixmap(":/images/icons/newsIcon");
	else if (topic == Sport)
		_icon = new QPixmap(":/images/icons/sportIcon");
	else if (topic == Adverts)
		_icon = new QPixmap(":/images/icons/advertsIcon");
	else if (topic == Economy)
		_icon = new QPixmap(":/icons/economyIcon");
	else if (topic == Culture)
		_icon = new QPixmap(":/images/icons/cultureIcon");
	else
		_icon = NULL;
}

void Article::setContent(const QString &text) {
    _text = text;
}

QPixmap Article::draw(const QRect &size) const {
    QPixmap res(size.width(), size.height());
    res.fill(Qt::transparent);

	QRect titleAdjustedRect = size.adjusted(10, 25, size.width(), size.height());
	int pixmapX = size.width() - 60;
	int pixmapY = 10;

    QPainter draw(&res);
    draw.setPen(Qt::black);
	draw.drawPixmap(pixmapX, pixmapY, 50, 50, *_icon);
	draw.drawText(titleAdjustedRect, Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap, _title);
    draw.drawText(size, Qt::AlignCenter | Qt::TextWordWrap, _text);
    draw.end();
    return res;
}

QPixmap Article::drawPreview(const QRect &size) const {
	QPixmap res(size.width(), size.height());
	res.fill(Qt::transparent);

	QRect titleAdjustedRect = size.adjusted(10, 25, size.width(), size.height());
	int pixmapX = size.width() - 60;
	int pixmapY = 10;

	QPainter draw(&res);
	draw.setPen(Qt::black);
	draw.drawPixmap(pixmapX, pixmapY, 50, 50, *_icon);
	draw.drawText(titleAdjustedRect, Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap, _title);
	draw.drawText(size, Qt::AlignCenter | Qt::TextWordWrap, _text);
	draw.end();
	return res;
}
