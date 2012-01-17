#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QtGui/QColor>

class Settings {
public:

    static QColor topBackroundColor() {
        return QColor(0xBE, 0x00, 0x02);
    }

    static QColor backroundButton() {
        return QColor(0xF0, 0xF0, 0xF0);
    }

    static QColor articleBackgroundColor() {
        return QColor(0xFF, 0xFF, 0xFF, 0xFF);
    }

    static QColor hourColor() {
        return QColor(0xF0, 0xF0, 0xF0);
    }
};

#endif // SETTINGS_HPP
