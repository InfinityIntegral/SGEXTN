#include "sgxrendercutevesiclessgwidget.h"
#include "../widgets/noninstantiable/sgwwidget.h"
#include "../widgets/instantiable/sgwcustomrenderer.h"

SGXRenderCuteVesiclesSGWidget::SGXRenderCuteVesiclesSGWidget() : SGWCustomRenderer(SGWWidget::rootWidget, ":/SGEXTN/cutevesicles/cutevesicles.qml", 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f){

}
