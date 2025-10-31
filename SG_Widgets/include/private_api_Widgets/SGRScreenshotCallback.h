#ifndef SGRSCREENSHOTCALLBACK_H
#define SGRSCREENSHOTCALLBACK_H

#include <QObject>
#include <QSharedPointer>
#include <private_api_Widgets/SG_Build_Widgets.h>

class SGRImage;
class QQuickItem;
class QQuickItemGrabResult;
class SG_WIDGETS_DLL SGRScreenshotCallback : public QObject
{
public:
    SGRScreenshotCallback(void (*callback)(SGRImage*), QQuickItem* item);
    void (*callbackFunction)(SGRImage*);
    QSharedPointer<QQuickItemGrabResult> screenshot;
    void doneProcessing();
};

#endif // SGRSCREENSHOTCALLBACK_H
