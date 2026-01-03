#ifndef SGWWIDGETDELETIONQUICKINTERFACE_H
#define SGWWIDGETDELETIONQUICKINTERFACE_H

#include <QObject>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWWidget;
class SG_WIDGETS_DLL SGWWidgetDeletionQuickInterface : public QObject {
public:
    SGWWidgetDeletionQuickInterface(SGWWidget* x);
    SGWWidget* x;
    void actuallyDeleteWidget() const;
};

#endif // SGWWIDGETDELETIONQUICKINTERFACE_H
