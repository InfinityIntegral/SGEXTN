#include "sgrscreenshotcallback.h"
#include <QQuickItemGrabResult>
#include <QQuickItem>
#include "../RendererInterface/sgrimage.h"

SGRScreenshotCallback::SGRScreenshotCallback(void (*callback)(SGRImage *), QQuickItem* item){
    callbackFunction = callback;
    (*this).screenshot = (*item).grabToImage();
    connect((*this).screenshot.data(), &QQuickItemGrabResult::ready, this, &SGRScreenshotCallback::doneProcessing);
}

void SGRScreenshotCallback::doneProcessing(){
    SGRImage* img = new SGRImage(1, 1);
    (*(*img).data) = (*screenshot).image();
    callbackFunction(img);
    screenshot.clear();
    screenshot = nullptr;
    delete this;
}
