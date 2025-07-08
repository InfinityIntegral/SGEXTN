#ifndef SGXTHEMECOLOURSPAGE_H
#define SGXTHEMECOLOURSPAGE_H

#include <QObject>
#include <QQuickItem>
#include <qtmetamacros.h>

class SGXThemeColoursPage : public QObject
{
    Q_OBJECT
public:
    SGXThemeColoursPage() = delete;
    static QQuickItem* instance;
    static void initialise();
signals:
    void doNothing();
public slots:
    static void activate();
};

#endif // SGXTHEMECOLOURSPAGE_H
