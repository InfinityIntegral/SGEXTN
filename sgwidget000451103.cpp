#include "sgwidget000451103.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGWidget000451103::SGWidget000451103(QWidget *parent, float x, float y, float h1, float h0){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour2);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000451103::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit + 0.5f * (SGCentralManagement::screenw - SGCentralManagement::renderw), y * SGCentralManagement::sizeunit + 0.5f * (SGCentralManagement::screenh - SGCentralManagement::renderh)));
    (*this).resize(QSize(SGCentralManagement::renderw, h1 * SGCentralManagement::renderh - h0 * SGCentralManagement::sizeunit));
}
