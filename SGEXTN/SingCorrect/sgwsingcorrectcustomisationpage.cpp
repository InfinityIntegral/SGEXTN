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
#include "../widgets/sgwstatusbar.h"
#include <QHash>
#include <qcontainerfwd.h>

SGWBackground* SGWSingCorrectCustomisationPage::instance = nullptr;
SGWButton* SGWSingCorrectCustomisationPage::enableButton = nullptr;
SGWButton* SGWSingCorrectCustomisationPage::disableButton = nullptr;
SGWInput* SGWSingCorrectCustomisationPage::prefixInput = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::prefixInvalidMessage = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::prefixUnsavedMessage = nullptr;
SGWInput* SGWSingCorrectCustomisationPage::customCharInput = nullptr;
SGWInput* SGWSingCorrectCustomisationPage::customCommandInput = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::customCharError = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::customCommandError = nullptr;
SGWWidget* SGWSingCorrectCustomisationPage::listParent = nullptr;
QHash<SGWButton*, QString>* SGWSingCorrectCustomisationPage::buttonsList = nullptr;

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
    SGWSingCorrectCustomisationPage::prefixInvalidMessage = new SGWTextLabel(p, "prefix cannot be blank", 0.0f, 2.1f, 0.0f, 1.0f, 1.0f, -2.1f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    SGWSingCorrectCustomisationPage::prefixUnsavedMessage = new SGWTextLabel(p, "press tab to save", 0.0f, 2.1f, 0.0f, 1.0f, 1.0f, -2.1f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    s = "    You can define custom SingCorrect commands that function exactly like builtin ones by entering the symbol (copy paste it from copychar.cc) and the command. Make sure that the command name does not overlap with any builtin command.";
    new SGWSequentialLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 3.0f, 8);
    new SGWTextLabel(p, "symbol", 0.25f, -2.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    new SGWTextLabel(p, "command", 0.25f, 0.1f, 0.0f, 0.0f, 0.5f, -0.2f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
    SGWSingCorrectCustomisationPage::customCharInput = new SGWTextInput(p, &SGWSingCorrectCustomisationPage::customCharCheck, 0.25f, -2.1f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGWSingCorrectCustomisationPage::customCommandInput = new SGWTextInput(p, &SGWSingCorrectCustomisationPage::customCommandCheck, 0.25f, 0.1f, 0.0f, 1.0f, 0.5f, -0.2f, 0.0f, 1.0f);
    new SGWTextButton(p, "add", &SGWSingCorrectCustomisationPage::addCustomCommand, 0.75f, 0.1f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGWSingCorrectCustomisationPage::customCharError = new SGWTextLabel(p, "single symbol", 0.25f, -2.1f, 0.0f, 2.0f, 0.0f, 4.0f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    SGWSingCorrectCustomisationPage::customCommandError = new SGWTextLabel(p, "only letters, not blank", 0.5f, -1.5f, 0.0f, 2.0f, 0.0f, 6.0f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    new SGWTextLabel(x, "custom SingCorrect commands:", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    SGWSingCorrectCustomisationPage::listParent = new SGWSequentialScrollView(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.5f, 0.0f, 0.5f, 8);
    SGWSingCorrectCustomisationPage::buttonsList = new QHash<SGWButton*, QString>();
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8);
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
    SGWSingCorrectCustomisationPage::refreshList();
}

void SGWSingCorrectCustomisationPage::activate(){
    SGWBackground::enable(SGWSingCorrectCustomisationPage::instance, &SGWSingCorrectCustomisationPage::initialise, &SGWSingCorrectCustomisationPage::reset);
}

void SGWSingCorrectCustomisationPage::exit(SGWButton */*unused*/){
    SGWBackground::disable(SGWSingCorrectCustomisationPage::instance);
    SGXSingCorrectCustomisation::syncFileData();
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

void SGWSingCorrectCustomisationPage::customCharCheck(SGWInput */*unused*/){
    const QString s = (*SGWSingCorrectCustomisationPage::customCharInput).getTextAsString();
    if(s.length() != 1){
        (*SGWSingCorrectCustomisationPage::customCharInput).setInvalid(true);
        (*SGWSingCorrectCustomisationPage::customCharError).setItemVisibility(true);
    }
    else{
        (*SGWSingCorrectCustomisationPage::customCharInput).setInvalid(false);
        (*SGWSingCorrectCustomisationPage::customCharError).setItemVisibility(false);
    }
}

void SGWSingCorrectCustomisationPage::customCommandCheck(SGWInput */*unused*/){
    QString s = (*SGWSingCorrectCustomisationPage::customCommandInput).getTextAsString();
    bool isValid = true;
    for(int i=0; i<s.length(); i++){
        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')){}
        else{isValid = false;}
    }
    if(s == ""){isValid = false;}
    if(isValid == false){
        (*SGWSingCorrectCustomisationPage::customCommandInput).setInvalid(true);
        (*SGWSingCorrectCustomisationPage::customCommandError).setItemVisibility(true);
    }
    else{
        (*SGWSingCorrectCustomisationPage::customCommandInput).setInvalid(false);
        (*SGWSingCorrectCustomisationPage::customCommandError).setItemVisibility(false);
    }
}

void SGWSingCorrectCustomisationPage::addCustomCommand(SGWButton */*unused*/){
    QString c = (*SGWSingCorrectCustomisationPage::customCharInput).getTextAsString();
    QString s = (*SGWSingCorrectCustomisationPage::customCommandInput).getTextAsString();
    bool isValid = true;
    if(c.length() != 1){isValid = false;}
    for(int i=0; i<s.length(); i++){
        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')){}
        else{isValid = false;}
    }
    if(s == ""){isValid = false;}
    if(isValid == false){
        SGWStatusBar::notify("invalid command");
        return;
    }
    (*SGXSingCorrectCustomisation::database).insert(s, c[0]);
    (*SGWSingCorrectCustomisationPage::customCharInput).setTextFromString("");
    (*SGWSingCorrectCustomisationPage::customCommandInput).setTextFromString("");
    (*SGWSingCorrectCustomisationPage::customCharInput).setInvalid(false);
    (*SGWSingCorrectCustomisationPage::customCommandInput).setInvalid(false);
    (*SGWSingCorrectCustomisationPage::customCharError).setItemVisibility(false);
    (*SGWSingCorrectCustomisationPage::customCommandError).setItemVisibility(false);
    SGWSingCorrectCustomisationPage::refreshList();
}

void SGWSingCorrectCustomisationPage::refreshList(){
    delete SGWSingCorrectCustomisationPage::buttonsList;
    SGWSingCorrectCustomisationPage::buttonsList = new QHash<SGWButton*, QString>();
    const QVector<SGWWidget*> c = (*SGWSingCorrectCustomisationPage::listParent).getChildren();
    for(int i=0; i<c.length(); i++){
        (*c.at(i)).deleteLater();
    }
    for(QHash<QString, QChar>::iterator i = (*SGXSingCorrectCustomisation::database).begin(); i != (*SGXSingCorrectCustomisation::database).end(); i++){
        SGWWidget* x = new SGWBlankWidget(SGWSingCorrectCustomisationPage::listParent, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 8);
        new SGWTextLabel(x, QString(i.value()), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
        new SGWTextLabel(x, i.key(), 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, -3.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
        SGWButton* b = new SGWTextButton(x, "x", &SGWSingCorrectCustomisationPage::deleteCommand, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        (*SGWSingCorrectCustomisationPage::buttonsList).insert(b, i.key());
    }
}

void SGWSingCorrectCustomisationPage::deleteCommand(SGWButton *button){
    (*SGXSingCorrectCustomisation::database).remove((*SGWSingCorrectCustomisationPage::buttonsList)[button]);
    SGWSingCorrectCustomisationPage::refreshList();
}
