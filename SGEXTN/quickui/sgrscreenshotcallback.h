#ifndef SGRSCREENSHOTCALLBACK_H
#define SGRSCREENSHOTCALLBACK_H

#include <QObject>
#include <QSharedPointer>

class SGRImage;
class QQuickItem;
class QQuickItemGrabResult;
class SGRScreenshotCallback : public QObject
{
public:
    SGRScreenshotCallback(void (*callback)(SGRImage*), QQuickItem* item);
    void (*callbackFunction)(SGRImage*);
    QSharedPointer<QQuickItemGrabResult> screenshot;
    void doneProcessing();
};

#endif // SGRSCREENSHOTCALLBACK_H
