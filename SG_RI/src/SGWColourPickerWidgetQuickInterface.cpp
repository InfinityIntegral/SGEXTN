#include <private_api_RI/SGWColourPickerWidgetQuickInterface.h>
#include <SGWColourPickerWidget.h>
#include <QQuickItem>
#include <QString>

SGWColourPickerWidgetQuickInterface::SGWColourPickerWidgetQuickInterface(SGWColourPickerWidget *x){
    (*this).x = x;
    connect((*x).getTopObject(), &QQuickItem::objectNameChanged, this, &SGWColourPickerWidgetQuickInterface::eventReceivedWithQString);
}

void SGWColourPickerWidgetQuickInterface::eventReceivedWithQString(const QString &event) const {
    const SGXString s = "";
    (*s.data) = event;
    (*x).eventReceived(s);
}
