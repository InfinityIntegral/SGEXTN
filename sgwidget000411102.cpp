#include "sgwidget000411102.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGWidget000411102::SGWidget000411102(QWidget *parent, float x, float y, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).h = h;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000411102::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit + 0.5f * (SGCentralManagement::screenw - SGCentralManagement::renderw), y * SGCentralManagement::sizeunit + 0.5f * (SGCentralManagement::screenh - SGCentralManagement::renderh)));
    (*this).resize(QSize(SGCentralManagement::renderw, h * SGCentralManagement::sizeunit));
}
