#include "sgwfontsizecustomisationpage.h"
#include "../widgets/noninstantiable/sgwbackground.h"
#include "../widgets/instantiable/sgwpagebackground.h"
#include "../widgets/instantiable/sgwsequentialscrollview.h"
#include "../widgets/instantiable/sgwtextbutton.h"
#include "../widgets/instantiable/sgwtextlabel.h"
#include "../widgets/instantiable/sgwsequentiallonglabel.h"
#include "../widgets/instantiable/sgwblankwidget.h"
#include "../widgets/instantiable/sgwtextinput.h"
#include "../customisation/sgxfontsizecustomisation.h"
#include "../notifications/sgwnotify.h"
#include "../widgets/instantiable/sgwsingletouchreceiver.h"
#include "../primitives/sgxtouchevent.h"
#include "../bypassquickui/sgxresizer.h"
#include "../math/sglfloatmath.h"
#include "../widgets/enums/sgwhorizontalalignment.h"

SGWBackground* SGWFontSizeCustomisationPage::instance = nullptr;
SGWButton* SGWFontSizeCustomisationPage::exitButton = nullptr;
SGWInput* SGWFontSizeCustomisationPage::sizeInput = nullptr;
SGWLabel* SGWFontSizeCustomisationPage::sizeInvalidMessage = nullptr;
SGWLabel* SGWFontSizeCustomisationPage::sizeUnsavedMessage = nullptr;
SGWBlankWidget* SGWFontSizeCustomisationPage::sliderForeground = nullptr;
SGWSingleTouchReceiver* SGWFontSizeCustomisationPage::sliderInput = nullptr;

void SGWFontSizeCustomisationPage::activate(){
    SGWBackground::enable(SGWFontSizeCustomisationPage::instance, &SGWFontSizeCustomisationPage::initialise, &SGWFontSizeCustomisationPage::reset);
}

SGWBackground* SGWFontSizeCustomisationPage::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 8);
    SGWWidget* realBg = new SGWSequentialScrollView(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -3.0f, 0.0f, 0.5f, 8);
    SGWFontSizeCustomisationPage::exitButton = new SGWTextButton(bg, "done", &SGWFontSizeCustomisationPage::exit, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    new SGWTextLabel(realBg, "Adjust text size", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, SGWHorizontalAlignment::Center, false);
    const SGXString s = "Use the slider and input field below to adjust the font size for the application. The font size can be set to a minimum of half the default font size and a maximum of double the default font size. Font size is automatically saved.";
    new SGWSequentialLongLabel(realBg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(realBg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    SGWWidget* p = new SGWBlankWidget(realBg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "font size:", 0.5f, -3.6f, 0.0f, 0.0f, 0.0f, 3.5f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    SGWFontSizeCustomisationPage::sizeInput = new SGWTextInput(p, &SGWFontSizeCustomisationPage::sizeValidityCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 4.0f, 0.0f, 1.0f);
    (*SGWFontSizeCustomisationPage::sizeInput).textChangedFunction = (&SGWFontSizeCustomisationPage::sizeUnsavedCheck);
    SGWFontSizeCustomisationPage::sizeUnsavedMessage = new SGWTextLabel(p, "press tab to save", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    SGWFontSizeCustomisationPage::sizeInvalidMessage = new SGWTextLabel(p, "number between 0.5 and 2", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 1.0f, -3.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWBlankWidget(p, 0.0f, 0.5f, 0.0f, 0.25f, 1.0f, -1.0f, 0.0f, 0.5f, 6);
    SGWFontSizeCustomisationPage::sliderForeground = new SGWBlankWidget(p, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 4);
    new SGWTextLabel(p, "0.5", 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.5f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    new SGWTextLabel(p, "2.0", 1.0f, -2.0f, 0.0f, 1.0f, 0.0f, 1.5f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWFontSizeCustomisationPage::sliderInput = new SGWSingleTouchReceiver(p, &SGWFontSizeCustomisationPage::sliderChange, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f);
    return bg;
}

void SGWFontSizeCustomisationPage::reset(){
    (*SGWFontSizeCustomisationPage::sizeInput).setTextFromFloat(SGXFontSizeCustomisation::fontSize / SGXFontSizeCustomisation::defaultFontSize);
    (*SGWFontSizeCustomisationPage::sizeUnsavedMessage).setItemVisibility(false);
    const float f = SGLFloatMath::logarithmBase2(SGXFontSizeCustomisation::fontSize / SGXFontSizeCustomisation::defaultFontSize);
    (*SGWFontSizeCustomisationPage::sliderForeground).setX1(0.5f + 0.5f * f);
    (*SGWFontSizeCustomisationPage::sliderForeground).setX0((-1.0f) * f - 0.5f);
}

void SGWFontSizeCustomisationPage::exit(){
    SGXFontSizeCustomisation::syncFontSize();
    SGWBackground::disable(SGWFontSizeCustomisationPage::instance);
    SGWNotify::notify("font size saved");
}

void SGWFontSizeCustomisationPage::sizeUnsavedCheck(){
    (*SGWFontSizeCustomisationPage::sizeUnsavedMessage).setItemVisibility(true);
    (*SGWFontSizeCustomisationPage::sizeInvalidMessage).setItemVisibility(false);
}

void SGWFontSizeCustomisationPage::sizeValidityCheck(){
    (*SGWFontSizeCustomisationPage::sizeUnsavedMessage).setItemVisibility(false);
    bool isValid = false;
    const float fontSize = (*SGWFontSizeCustomisationPage::sizeInput).getTextAsFloat(&isValid, 0.5f, 2.0f);
    if(isValid == false){
        (*SGWFontSizeCustomisationPage::sizeInvalidMessage).setItemVisibility(true);
        (*SGWFontSizeCustomisationPage::sizeInput).setInvalid(true);
        return;
    }
    const float f = SGLFloatMath::logarithmBase2(fontSize);
    (*SGWFontSizeCustomisationPage::sliderForeground).setX1(0.5f + 0.5f * f);
    (*SGWFontSizeCustomisationPage::sliderForeground).setX0((-1.0f) * f - 0.5f);
    (*SGWFontSizeCustomisationPage::sizeInvalidMessage).setItemVisibility(false);
    (*SGWFontSizeCustomisationPage::sizeInput).setInvalid(false);
    SGXFontSizeCustomisation::fontSize = fontSize * SGXFontSizeCustomisation::defaultFontSize;
    SGXFontSizeCustomisation::updateFontSize();
}

void SGWFontSizeCustomisationPage::sliderChange(const SGXTouchEvent &x){
    if(x.phase == SGXTouchEvent::TouchEnd){
        (*SGWFontSizeCustomisationPage::sliderForeground).setThemeColour(4);
        (*SGWFontSizeCustomisationPage::sliderInput).setH1(0.0f);
        return;
    }
    (*SGWFontSizeCustomisationPage::sliderForeground).setThemeColour(2);
    (*SGWFontSizeCustomisationPage::sliderInput).setH1(100.0f);
    (*SGWFontSizeCustomisationPage::sizeInput).setInvalid(false);
    (*SGWFontSizeCustomisationPage::sizeInvalidMessage).setItemVisibility(false);
    float f = x.x / (*SGWFontSizeCustomisationPage::sliderInput).getWidth();
    const float limit = 0.5f * SGXResizer::getSizeUnit() / (SGXResizer::getRenderSpaceWidth() - SGXResizer::getSizeUnit());
    f = (f - limit) / (1 - 2 * limit);
    f = 2.0f * (f - 0.5f);
    if(f < -1.0f){f = -1.0f;}
    else if(f > 1.0f){f = 1.0f;}
    (*SGWFontSizeCustomisationPage::sliderForeground).setX1(0.5f + 0.5f * f);
    (*SGWFontSizeCustomisationPage::sliderForeground).setX0((-1.0f) * f - 0.5f);
    f = SGLFloatMath::twoToThePowerOfThis(f);
    (*SGWFontSizeCustomisationPage::sizeInput).setTextFromFloat(f);
    (*SGWFontSizeCustomisationPage::sizeUnsavedMessage).setItemVisibility(false);
    SGXFontSizeCustomisation::fontSize = f * SGXFontSizeCustomisation::defaultFontSize;
    SGXFontSizeCustomisation::updateFontSize();
}
