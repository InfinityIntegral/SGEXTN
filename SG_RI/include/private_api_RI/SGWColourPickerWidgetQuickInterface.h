#ifndef SGWCOLOURPICKERWIDGETQUICKINTERFACE_H
#define SGWCOLOURPICKERWIDGETQUICKINTERFACE_H

#include <QObject>

#include <private_api_RI/SG_Build_RI.h>

class SGXString;
class SGWColourPickerWidget;
class SG_RI_DLL SGWColourPickerWidgetQuickInterface : public QObject {
public:
    SGWColourPickerWidgetQuickInterface(SGWColourPickerWidget* x);
    SGWColourPickerWidget* x;
    void eventReceivedWithQString(const QString& event) const;
};

#endif // SGWCOLOURPICKERWIDGETQUICKINTERFACE_H
