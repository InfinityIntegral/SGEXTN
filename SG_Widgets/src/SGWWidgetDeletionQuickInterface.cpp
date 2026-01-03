#include <private_api_Widgets/SGWWidgetDeletionQuickInterface.h>
#include <SGWWidget.h>

SGWWidgetDeletionQuickInterface::SGWWidgetDeletionQuickInterface(SGWWidget *x){
    (*this).x = x;
}

void SGWWidgetDeletionQuickInterface::actuallyDeleteWidget() const {
    delete x;
}
