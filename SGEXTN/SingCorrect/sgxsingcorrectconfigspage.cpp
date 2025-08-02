#include "sgxsingcorrectconfigspage.h"
#include "../quickui/sgxquickuiinterface.h"
#include "sgxsingcorrectcustomisation.h"
#include "../template/sgxstatusbar.h"
#include <QQuickItem>
#include "sgxsingcorrectcore.h"
#include <QString>

QQuickItem* SGXSingCorrectConfigsPage::instance = nullptr;
QQuickItem* SGXSingCorrectConfigsPage::disableButton = nullptr;
QQuickItem* SGXSingCorrectConfigsPage::enableButton = nullptr;
QQuickItem* SGXSingCorrectConfigsPage::prefixInput = nullptr;
QQuickItem* SGXSingCorrectConfigsPage::customAddCommandInput = nullptr;
QQuickItem* SGXSingCorrectConfigsPage::customAddCharInput = nullptr;

QQuickItem* SGXSingCorrectConfigsPage::initialise(){
    SGXSingCorrectConfigsPage::instance = SGXQuickUIInterface::createWidget(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 8, false);
    QQuickItem* bg = SGXQuickUIInterface::createScrollView(SGXSingCorrectConfigsPage::instance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -2.0f, 0.0f, 30.0f, 0.0f, 0.5f, 8, false);
    SGXQuickUIInterface::createTextButton(SGXSingCorrectConfigsPage::instance, "cancel", &SGXSingCorrectConfigsPage::cancelChanges, 0.0f, 0.0f, 1.0f, -2.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createTextButton(SGXSingCorrectConfigsPage::instance, "save changes", &SGXSingCorrectConfigsPage::confirmChanges, 0.5f, 0.0f, 1.0f, -2.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createTitle(bg, "SingCorrect configs", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 2.0f);
    const QString modulePrompt = "This app is based on the SGEXTN framework which has a module called SingCorrect. SingCorrect allows you to input Math, Science, Computer Science, and random Unicode characters easily by replacing LaTeX style SingCorrect commands with the actual characters. SingCorrect supports most of the LaTeX characters supported by KaTeX and the Art of Problem Solving (AoPS) platform.";
    SGXQuickUIInterface::createLongText(bg, modulePrompt, 0.0f, 0.5f, 0.0f, 3.0f, 1.0f, -1.5f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXQuickUIInterface::createRightText(bg, "use SingCorrect?", 0.5f, -5.6f, 0.0f, 6.5f, 0.0f, 5.5f, 0.0f, 1.0f);
    SGXSingCorrectConfigsPage::enableButton = SGXQuickUIInterface::createTextButton(bg, "yes", &SGXSingCorrectConfigsPage::enableModule, 0.5f, 0.1f, 0.0f, 6.5f, 0.0f, 1.5f, 0.0f, 1.0f);
    SGXSingCorrectConfigsPage::disableButton = SGXQuickUIInterface::createTextButton(bg, "no", &SGXSingCorrectConfigsPage::disableModule, 0.5f, 1.7f, 0.0f, 6.5f, 0.0f, 1.5f, 0.0f, 1.0f);
    const QString prefixPrompt = "The prefix is used by SingCorrect to identify and autocorrect SingCorrect commands. It does nothing if SingCorrect is disabled. By default, the prefix is SG-\\ so a valid SingCorrect command would be SG-\\SGhome but you can change the prefix. Use the prefix \\ for a LaTeX feel, in which case the same command would be \\SGhome";
    SGXQuickUIInterface::createLongText(bg, prefixPrompt, 0.0f, 0.5f, 0.0f, 8.0f, 1.0f, -1.5f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXQuickUIInterface::createRightText(bg, "prefix:", 0.5f, -2.6f, 0.0f, 11.5f, 0.0f, 2.5f, 0.0f, 1.0f);
    SGXSingCorrectConfigsPage::prefixInput = SGXQuickUIInterface::createInputField(bg, 0.5f, 0.1f, 0.0f, 11.5f, 0.0f, 4.0f, 0.0f, 1.0f);
    const QString customPrompt = "You can use the options below to add and delete custom commands, note that the command can only contain uppercase and lowercase letters.";
    SGXQuickUIInterface::createLongText(bg, customPrompt, 0.0f, 0.5f, 0.0f, 13.0f, 1.0f, -1.5f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXQuickUIInterface::createRightText(bg, "command:", 0.5f, -4.1f, 0.0f, 16.5f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXSingCorrectConfigsPage::customAddCommandInput = SGXQuickUIInterface::createInputField(bg, 0.5f, 0.1f, 0.0f, 16.5f, 0.5f, -1.1f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(bg, "character:", 0.5f, -4.6f, 0.0f, 18.0f, 0.0f, 4.5f, 0.0f, 1.0f);
    SGXSingCorrectConfigsPage::customAddCharInput = SGXQuickUIInterface::createInputField(bg, 0.5f, 0.1f, 0.0f, 18.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createTextButton(bg, "add", &SGXSingCorrectConfigsPage::addCustomCharacter, 0.5f, 2.6f, 0.0f, 18.0f, 0.0f, 1.5f, 0.0f, 1.0f);
    return SGXSingCorrectConfigsPage::instance;
}

void SGXSingCorrectConfigsPage::reset(){
    SGXSingCorrectCustomisation::syncFileData();
    if(SGXSingCorrectCustomisation::moduleEnabled == true){
        SGXQuickUIInterface::setButtonSelected(SGXSingCorrectConfigsPage::enableButton);
        SGXQuickUIInterface::setButtonUnselected(SGXSingCorrectConfigsPage::disableButton);
    }
    else{
        SGXQuickUIInterface::setButtonUnselected(SGXSingCorrectConfigsPage::enableButton);
        SGXQuickUIInterface::setButtonSelected(SGXSingCorrectConfigsPage::disableButton);
    }
    SGXQuickUIInterface::setInputFieldDataUsingString(SGXSingCorrectConfigsPage::prefixInput, SGXSingCorrectCore::correctionPrefix);
    SGXQuickUIInterface::setInputFieldDataUsingString(SGXSingCorrectConfigsPage::customAddCommandInput, "");
    SGXQuickUIInterface::setInputFieldDataUsingString(SGXSingCorrectConfigsPage::customAddCharInput, "");
}

void SGXSingCorrectConfigsPage::activate(){
    SGXQuickUIInterface::showPage(SGXSingCorrectConfigsPage::instance, &SGXSingCorrectConfigsPage::initialise, &SGXSingCorrectConfigsPage::reset);
}

void SGXSingCorrectConfigsPage::cancelChanges(){
    SGXSingCorrectCustomisation::loadFileData();
    SGXQuickUIInterface::hidePage(SGXSingCorrectConfigsPage::instance);
}

void SGXSingCorrectConfigsPage::confirmChanges(){
    bool ignore = false;
    const QString prefix = SGXQuickUIInterface::getInputFieldDataAsString(SGXSingCorrectConfigsPage::prefixInput, ignore);
    if(prefix == ""){
        SGXQuickUIInterface::setInputFieldInvalid(SGXSingCorrectConfigsPage::prefixInput);
        SGXStatusBar::notify("prefix cannot be blank", 5);
        return;
    }
    SGXSingCorrectCore::correctionPrefix = prefix;
    SGXSingCorrectCustomisation::syncFileData();
    SGXStatusBar::notify("SingCorrect configs updated", 5);
    SGXQuickUIInterface::hidePage(SGXSingCorrectConfigsPage::instance);
}

void SGXSingCorrectConfigsPage::disableModule(){
    SGXSingCorrectCustomisation::moduleEnabled = false;
    SGXQuickUIInterface::setButtonUnselected(SGXSingCorrectConfigsPage::enableButton);
    SGXQuickUIInterface::setButtonSelected(SGXSingCorrectConfigsPage::disableButton);
}

void SGXSingCorrectConfigsPage::enableModule(){
    SGXSingCorrectCustomisation::moduleEnabled = true;
    SGXQuickUIInterface::setButtonSelected(SGXSingCorrectConfigsPage::enableButton);
    SGXQuickUIInterface::setButtonUnselected(SGXSingCorrectConfigsPage::disableButton);
}

void SGXSingCorrectConfigsPage::addCustomCharacter(){
    bool ignore = false;
    QString customCommand = SGXQuickUIInterface::getInputFieldDataAsString(SGXSingCorrectConfigsPage::customAddCommandInput, ignore);
    if(customCommand == ""){
        SGXStatusBar::notify("command cannot be empty", 5);
        SGXQuickUIInterface::setInputFieldInvalid(SGXSingCorrectConfigsPage::customAddCommandInput);
        return;
    }
    bool commandValid = true;
    for(int i=0; i<customCommand.length(); i++){
        if((customCommand[i] >= 'a' && customCommand[i] <= 'z') || (customCommand[i] >= 'A' && customCommand[i] <= 'Z')){}
        else{commandValid = false;}
    }
    if(commandValid == false){
        SGXStatusBar::notify("command can only contain letters", 5);
        SGXQuickUIInterface::setInputFieldInvalid(SGXSingCorrectConfigsPage::customAddCommandInput);
        return;
    }
    QString customChar = SGXQuickUIInterface::getInputFieldDataAsString(SGXSingCorrectConfigsPage::customAddCharInput, ignore);
    if(customChar.length() != 1){
        SGXStatusBar::notify("character must have length 1", 5);
        SGXQuickUIInterface::setInputFieldInvalid(SGXSingCorrectConfigsPage::customAddCharInput);
        return;
    }
    SGXQuickUIInterface::setInputFieldDataUsingString(SGXSingCorrectConfigsPage::customAddCommandInput, "");
    SGXQuickUIInterface::setInputFieldDataUsingString(SGXSingCorrectConfigsPage::customAddCharInput, "");
    (*SGXSingCorrectCustomisation::database).insert(customCommand, customChar[0]);
}
