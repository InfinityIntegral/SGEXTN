#include "sgxrendercutevesiclessgwidget.h"
#include "../widgets/sgwwidget.h"
#include "../widgets/sgwcustomrenderer.h"
#include <QObject>

SGXRenderCuteVesiclesSGWidget::SGXRenderCuteVesiclesSGWidget() : SGWCustomRenderer(SGWWidget::rootWidget, ":/SGEXTN/cutevesicles/cutevesicles.qml", 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f){
    
}
