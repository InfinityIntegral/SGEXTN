#include "sgrootwindow.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGRootWindow::SGRootWindow(){
    (*SGCentralManagement::signalsemitter).setParent(this);
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    (*this).setAutoFillBackground(true);
    (*this).t = new QTimer(this);
    connect((*this).t, &QTimer::timeout, this, &SGRootWindow::updatescreensize);
    (*(*this).t).start(1000);
}

void SGRootWindow::updatescreensize(){
    float lastw = SGCentralManagement::screenw;
    float lasth = SGCentralManagement::screenh;
    SGCentralManagement::screenw = (*SGCentralManagement::rootwindow).size().width();
    SGCentralManagement::screenh = (*SGCentralManagement::rootwindow).size().height();
    if(lastw != SGCentralManagement::screenw || lasth != SGCentralManagement::screenh){
        if(SGCentralManagement::screenw > 16.0f/9.0f * SGCentralManagement::screenh){
            SGCentralManagement::renderw = 16.0f/9.0f * SGCentralManagement::screenh;
            SGCentralManagement::renderh = SGCentralManagement::screenh;
        }
        else if(SGCentralManagement::screenw < 9.0f/16.0f * SGCentralManagement::screenh){
            SGCentralManagement::renderw = SGCentralManagement::screenw;
            SGCentralManagement::renderh = 16.0f/9.0f * SGCentralManagement::screenw;
        }
        else{
            SGCentralManagement::renderw = SGCentralManagement::screenw;
            SGCentralManagement::renderh = SGCentralManagement::screenh;
        }
        SGCentralManagement::sizeunit = 1.0f/24.0f * std::max(SGCentralManagement::renderw, SGCentralManagement::renderh);
        (*SGCentralManagement::signalsemitter).sendsignals();
    }
}
