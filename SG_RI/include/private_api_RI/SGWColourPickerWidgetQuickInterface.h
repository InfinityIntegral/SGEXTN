#ifndef SGWCOLOURPICKERWIDGETQUICKINTERFACE_H
#define SGWCOLOURPICKERWIDGETQUICKINTERFACE_H

#include <QObject>

class SGXString;
class SGWColourPickerWidget;
class SGWColourPickerWidgetQuickInterface : public QObject {
public:
    SGWColourPickerWidgetQuickInterface(SGWColourPickerWidget* x);
    SGWColourPickerWidget* x;
    void eventReceivedWithQString(const QString& event) const;
};

#endif // SGWCOLOURPICKERWIDGETQUICKINTERFACE_H
