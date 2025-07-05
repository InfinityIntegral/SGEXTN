#ifndef SGXCOLOURPICKER_H
#define SGXCOLOURPICKER_H

#include <QObject>
#include <QQuickItem>

class SGXColourPicker : public QObject
{
    Q_OBJECT
public:
    SGXColourPicker() = delete;
    static void initialise();
    static void activate();
    static QQuickItem* instance;
    static QQuickItem* targetInput;
};

#endif // SGXCOLOURPICKER_H
