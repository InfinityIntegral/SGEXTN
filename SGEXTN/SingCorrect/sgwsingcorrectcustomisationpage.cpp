#include "sgwsingcorrectcustomisationpage.h"
#include "../widgets/sgwpagebackground.h"
#include "../widgets/sgwtextbutton.h"
#include "../widgets/sgwsequentialscrollview.h"
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwbutton.h"
#include "../widgets/sgwwidget.h"
#include "../widgets/sgwtextlabel.h"
#include "../widgets/sgwblankwidget.h"
#include "../widgets/sgwhorizontalalignment.h"
#include "../widgets/sgwsequentiallonglabel.h"
#include "../widgets/sgwtextinput.h"
#include "sgxsingcorrectcustomisation.h"
#include <QString>
#include "sgxsingcorrectcore.h"
#include "../widgets/sgwinput.h"
#include "../widgets/sgwlabel.h"

SGWBackground* SGWSingCorrectCustomisationPage::instance = nullptr;
SGWButton* SGWSingCorrectCustomisationPage::enableButton = nullptr;
SGWButton* SGWSingCorrectCustomisationPage::disableButton = nullptr;
SGWInput* SGWSingCorrectCustomisationPage::prefixInput = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::prefixInvalidMessage = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::prefixUnsavedMessage = nullptr;

SGWBackground* SGWSingCorrectCustomisationPage::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 8);
    SGWWidget* x = new SGWSequentialScrollView(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8);
    new SGWTextLabel(x, "SingCorrect configs", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, SGWHorizontalAlignment::Center, false);
    QString s = "    SingCorrect is a module builtin to SGEXTN that allows you to type special characters, including mathematical and scientific symbols, superscripts and subscripts, Optical Answer Sheet bubbles, and emojis in any SGEXTN input field. This is done by inputting LaTeX style commands, but the prefix is not fixed at \\, instead it is user-configurable and default set to SG-\\. After entering the command, press space to show the symbol.\n    This page is used to configure SingCorrect. Changes are applied immediately and can be verified in the input field provided below. (Try to enter: SG-\\SGhome )";
    new SGWSequentialLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8);
    new SGWTextInput(x, nullptr, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 8);
    new SGWTextButton(x, "builtin command list", nullptr, 0.5f, -4.0f, 0.0f, 0.0f, 0.0f, 8.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 8);
    SGWWidget* p = new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.5f, 8);
    new SGWTextLabel(p, "use SingCorrect?", 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, -0.1f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWSingCorrectCustomisationPage::enableButton = new SGWTextButton(p, "yes", &SGWSingCorrectCustomisationPage::enableFunction, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGWSingCorrectCustomisationPage::disableButton = new SGWTextButton(p, "no", &SGWSingCorrectCustomisationPage::disableFunction, 0.5f, 2.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    s = "    The prefix, default being SG-\\, determines what text is recognised as SingCorrect commands. Use the prefix \\ for similarity to LaTeX.";
    new SGWSequentialLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "prefix:", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWSingCorrectCustomisationPage::prefixInput = new SGWTextInput(p, &SGWSingCorrectCustomisationPage::prefixSaved, 0.0f, 2.1f, 0.0f, 0.0f, 1.0f, -2.1f, 0.0f, 1.0f);
    (*SGWSingCorrectCustomisationPage::prefixInput).setTextChangedFunction(&SGWSingCorrectCustomisationPage::prefixUpdated);
    SGWSingCorrectCustomisationPage::prefixUnsavedMessage = new SGWTextLabel(p, "press tab to save", 0.0f, 2.1f, 0.0f, 1.0f, 1.0f, -2.1f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    SGWSingCorrectCustomisationPage::prefixInvalidMessage = new SGWTextLabel(p, "prefix cannot be blank", 0.0f, 2.1f, 0.0f, 1.0f, 1.0f, -2.1f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    new SGWTextButton(bg, "done", &SGWSingCorrectCustomisationPage::exit, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    return bg;
}

void SGWSingCorrectCustomisationPage::reset(){
    if(SGXSingCorrectCustomisation::moduleEnabled == true){
        (*SGWSingCorrectCustomisationPage::enableButton).setSelected(true);
        (*SGWSingCorrectCustomisationPage::disableButton).setSelected(false);
    }
    else{
        (*SGWSingCorrectCustomisationPage::enableButton).setSelected(false);
        (*SGWSingCorrectCustomisationPage::disableButton).setSelected(true);
    }
    (*SGWSingCorrectCustomisationPage::prefixInput).setTextFromString(SGXSingCorrectCore::correctionPrefix);
    (*SGWSingCorrectCustomisationPage::prefixUnsavedMessage).setItemVisibility(false);
}

void SGWSingCorrectCustomisationPage::activate(){
    SGWBackground::enable(SGWSingCorrectCustomisationPage::instance, &SGWSingCorrectCustomisationPage::initialise, &SGWSingCorrectCustomisationPage::reset);
}

void SGWSingCorrectCustomisationPage::exit(SGWButton */*unused*/){
    SGWBackground::disable(SGWSingCorrectCustomisationPage::instance);
}

void SGWSingCorrectCustomisationPage::enableFunction(SGWButton */*unused*/){
    SGXSingCorrectCustomisation::moduleEnabled = true;
    (*SGWSingCorrectCustomisationPage::enableButton).setSelected(true);
    (*SGWSingCorrectCustomisationPage::disableButton).setSelected(false);
}

void SGWSingCorrectCustomisationPage::disableFunction(SGWButton */*unused*/){
    SGXSingCorrectCustomisation::moduleEnabled = false;
    (*SGWSingCorrectCustomisationPage::enableButton).setSelected(false);
    (*SGWSingCorrectCustomisationPage::disableButton).setSelected(true);
}

void SGWSingCorrectCustomisationPage::prefixUpdated(SGWInput */*unused*/){
    (*SGWSingCorrectCustomisationPage::prefixUnsavedMessage).setItemVisibility(true);
}

void SGWSingCorrectCustomisationPage::prefixSaved(SGWInput */*unused*/){
    (*SGWSingCorrectCustomisationPage::prefixUnsavedMessage).setItemVisibility(false);
    const QString prefix = (*SGWSingCorrectCustomisationPage::prefixInput).getTextAsString();
    if(prefix == ""){
        (*SGWSingCorrectCustomisationPage::prefixInvalidMessage).setItemVisibility(true);
        (*SGWSingCorrectCustomisationPage::prefixInput).setInvalid(true);
        return;
    }
    (*SGWSingCorrectCustomisationPage::prefixInvalidMessage).setItemVisibility(false);
    (*SGWSingCorrectCustomisationPage::prefixInput).setInvalid(false);
    SGXSingCorrectCore::correctionPrefix = prefix;
}
