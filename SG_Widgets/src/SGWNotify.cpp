#include <SGWNotify.h>
#include <SGWTextLabel.h>
#include <SGXTimer.h>
#include <SGLQueue.h>
#include <SGWWidget.h>
#include <SGWLabel.h>
#include <SGXString.h>
#include <SGWHorizontalAlignment.h>
#include <SGWVerticalAlignment.h>

float SGWNotify::timeShown = 3.0f;
SGLQueue<const SGWWidget*>* SGWNotify::instance = nullptr;
float SGWNotify::animationLength = 0.5f;
bool SGWNotify::animationState = false;
int SGWNotify::animationStage = 0;
SGWLabel* SGWNotify::pullDownInstance = nullptr;
SGXTimer* SGWNotify::pullDownTimer = nullptr;

void SGWNotify::terminate(){
    delete (*SGWNotify::instance).front();
    (*SGWNotify::instance).pop();
}

void SGWNotify::notify(const SGXString &s){
    const SGWLabel* x = new SGWTextLabel(SGWWidget::rootWidget, s, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
    if(SGWNotify::instance == nullptr){SGWNotify::instance = new SGLQueue<const SGWWidget*>();}
    (*SGWNotify::instance).push(x);
    SGXTimer::singleCall(SGWNotify::timeShown, &SGWNotify::terminate);
}

void SGWNotify::animate(){
    if(SGWNotify::animationState == false){SGWNotify::animationStage++;}
    else{SGWNotify::animationStage--;}
    if(SGWNotify::animationStage == 24){SGWNotify::animationState = true;}
    if(SGWNotify::animationStage == 0){
        SGWNotify::notify((*SGWNotify::pullDownInstance).getTextAsString());
        delete SGWNotify::pullDownInstance;
        SGWNotify::pullDownInstance = nullptr;
        delete SGWNotify::pullDownTimer;
        SGWNotify::pullDownTimer = nullptr;
        SGWNotify::animationStage = 0;
        SGWNotify::animationState = false;
    }
    else{
        (*SGWNotify::pullDownInstance).setH1(static_cast<float>(SGWNotify::animationStage) / 24.0f);
        (*SGWNotify::pullDownInstance).setH0(static_cast<float>(24 - SGWNotify::animationStage) / 24.0f);
    }
}

void SGWNotify::pullDownNotify(const SGXString &s){
    delete SGWNotify::pullDownInstance;
    SGWNotify::pullDownInstance = nullptr;
    delete SGWNotify::pullDownTimer;
    SGWNotify::pullDownTimer = nullptr;
    SGWNotify::animationStage = 0;
    SGWNotify::animationState = false;
    SGWNotify::pullDownInstance = new SGWTextLabel(SGWWidget::rootWidget, s, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
    (*SGWNotify::pullDownInstance).setVerticalAlignment(SGWVerticalAlignment::Bottom);
    SGWNotify::pullDownTimer = new SGXTimer(SGWNotify::animationLength / 48.0f, &SGWNotify::animate);
}
