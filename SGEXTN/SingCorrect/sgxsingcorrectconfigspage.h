#ifndef SGXSINGCORRECTCONFIGSPAGE_H
#define SGXSINGCORRECTCONFIGSPAGE_H

#include <QObject>
#include <QQuickItem>
#include <qtmetamacros.h>

class SGXSingCorrectConfigsPage : public QObject
{
    Q_OBJECT
public:
    SGXSingCorrectConfigsPage() = delete;
    static QQuickItem* initialise();
    static void reset();
    static QQuickItem* instance;
    static QQuickItem* disableButton;
    static QQuickItem* enableButton;
signals:
    void doNothing();
public slots:
    static void activate();
    static void enableModule();
    static void disableModule();
    static void cancelChanges();
    static void confirmChanges();
};

#endif // SGXSINGCORRECTCONFIGSPAGE_H
