#include "sgwwidgetquickinterface.h"
#include "../widgets/noninstantiable/sgwwidget.h"
#include "../widgets/enums/sgwtype.h"
#include "../widgets/noninstantiable/sgwbutton.h"
#include "../widgets/instantiable/sgwcolourpickerwidget.h"
#include "../widgets/noninstantiable/sgwinput.h"
#include "../widgets/unique/sgwstatusbar.h"
#include "../widgets/instantiable/sgwtouchreceiver.h"
#include <QQuickItem>
#include "../primitives/sgxstring.h"

SGWWidgetQuickInterface::SGWWidgetQuickInterface(SGWWidget *x){
    (*this).x = x;
    connect((*x).getTopObject(), &QQuickItem::objectNameChanged, this, &SGWWidgetQuickInterface::eventReceivedWithQString);
}

void SGWWidgetQuickInterface::eventReceivedWithQString(const QString &event) const {
    const SGXString s = "";
    (*s.data) = event;
    eventReceived(s);
}

void SGWWidgetQuickInterface::eventReceived(const SGXString &event) const {
    if(SGWType::isButton((*x).getType()) == true){(*static_cast<SGWButton*>(x)).eventReceived(event);}
    else if(SGWType::isInputField((*x).getType()) == true){(*static_cast<SGWInput*>(x)).eventReceived(event);}
    else if((*x).getType() == SGWType::ColourPicker){(*static_cast<SGWColourPickerWidget*>(x)).eventReceived(event);}
    else if((*x).getType() == SGWType::TouchReceiver){(*static_cast<SGWTouchReceiver*>(x)).eventReceived(event);}
    else if((*x).getType() == SGWType::StatusBar){SGWStatusBar::eventReceived(event);}
}
