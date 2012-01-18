#include "article.hpp"

#include <QtGui/QApplication>
#include <QtGui/QPainter>

Article::Article() {
}

void Article::setContent(const QString &title, const QString &text, Topic topic) {
	_title = title;
	_text = text;

	if (topic == News)
		_icon = new QPixmap(":/icons/newsIcon");
	else if (topic == Sport)
		_icon = new QPixmap(":/icons/sportIcon");
	else if (topic == Adverts)
		_icon = new QPixmap(":/icons/advertsIcon");
	else if (topic == Economy)
		_icon = new QPixmap(":/icons/economyIcon");
	else if (topic == Culture)
		_icon = new QPixmap(":/icons/cultureIcon");
	else
		_icon = NULL;
}

void Article::setContent(const QString &text) {
    _text = text;
}

QPixmap Article::drawArticle(const QRect &size) const {
	QRect titleAdjustedRect = QRect(10, 25, size.width() - 120, 60);
	QRect contentAdjustedRect = size.adjusted(10, titleAdjustedRect.height() + 10, -10, 0);
	return draw(size, titleAdjustedRect, contentAdjustedRect);
}

QPixmap Article::drawPreview(const QRect &size) const {
	QRect titleAdjustedRect = QRect(10, 25, size.width() - 120 , 60);
	QRect contentAdjustedRect = size.adjusted(10, titleAdjustedRect.height() + 10, -10, 0);
	return draw(size, titleAdjustedRect, contentAdjustedRect);
}

QPixmap Article::draw(const QRect &size, const QRect &titleRect, const QRect &contentRect) const {
	QPixmap res(size.width(), size.height());
	res.fill(Qt::transparent);

	int pixmapX = size.width() - 60;
	int pixmapY = 10;

	QPainter draw(&res);
	draw.setPen(Qt::black);
	draw.drawPixmap(pixmapX, pixmapY, 50, 50, *_icon);
	draw.drawText(contentRect, Qt::AlignJustify | Qt::TextWordWrap, _text);
	QFont font = draw.font();
	font.setBold(true);
	draw.setFont(font);
	draw.drawText(titleRect, Qt::AlignJustify | Qt::TextWordWrap, _title);
	draw.end();
	return res;
}
