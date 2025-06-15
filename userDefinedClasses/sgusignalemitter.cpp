#include "sgusignalemitter.h"

void SGUSignalEmitter::sendSignals(){
    emit (*this).updateScreen(); // NOLINT
    // emit your signals here based on what widgets are visible
    // assuming SGCManagementClass::someWidget is a raw pointer to a SGEXTN widget
    // if(SGCManagementClass::someWidget != nullptr && (*SGCManagementClass::someWidget).isVisible() == true){
    //     emit (*this).yourSignal(); // NOLINT
    // }
    // this will allow your own widgets to resize properly
    // note that in your code, you can use
    // emit (*SGXCentral::signalEmitter).yourSignal();
    // to trigger UI refresh even if a resize did not occur
    // use NOLINT on all signal emission because emit is not real
    // do not use single line if conditional so that NOLINT does not cover the condition
}
