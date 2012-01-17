#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QtGui/QColor>

class Settings {
public:
    static QColor backgroundColor() {
        return QColor(0xE9, 0x27, 0x27);
    }

    static QColor foregroundColor() {
        return QColor(0xFF, 0xCA, 0xCA);
    }

    static QColor topBackroundColor() {
        return QColor(0xBE, 0x00, 0x02);
    }

    static QColor backroundButton() {
        return QColor(0xF0, 0xF0, 0xF0);
    }
};

#endif // SETTINGS_HPP
