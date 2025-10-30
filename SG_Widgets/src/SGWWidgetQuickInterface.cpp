#include <private_api_Widgets/SGWWidgetQuickInterface.h>
#include <SGWWidget.h>
#include <SGWType.h>
#include <SGWButton.h>
#include <SGWInput.h>
#include <private_api_Widgets/SGWStatusBar.h>
#include <SGWMultiTouchReceiver.h>
#include <QQuickItem>
#include <SGXString.h>
#include <SGWSingleTouchReceiver.h>

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
    else if((*x).getType() == SGWType::MultiTouchReceiver){(*static_cast<SGWMultiTouchReceiver*>(x)).eventReceived(event);}
    else if((*x).getType() == SGWType::SingleTouchReceiver){(*static_cast<SGWSingleTouchReceiver*>(x)).eventReceived(event);}
}
