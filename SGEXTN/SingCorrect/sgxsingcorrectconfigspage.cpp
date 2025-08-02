#include "sgxsingcorrectconfigspage.h"
#include "../quickui/sgxquickuiinterface.h"
#include "sgxsingcorrectcustomisation.h"
#include "../template/sgxstatusbar.h"
#include <QQuickItem>

QQuickItem* SGXSingCorrectConfigsPage::instance = nullptr;
QQuickItem* SGXSingCorrectConfigsPage::disableButton = nullptr;
QQuickItem* SGXSingCorrectConfigsPage::enableButton = nullptr;

QQuickItem* SGXSingCorrectConfigsPage::initialise(){
    SGXSingCorrectConfigsPage::instance = SGXQuickUIInterface::createWidget(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 8, false);
    QQuickItem* bg = SGXQuickUIInterface::createScrollView(SGXSingCorrectConfigsPage::instance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -2.0f, 0.0f, 10.0f, 0.0f, 0.5f, 8, false);
    SGXQuickUIInterface::createTextButton(SGXSingCorrectConfigsPage::instance, "cancel", &SGXSingCorrectConfigsPage::cancelChanges, 0.0f, 0.0f, 1.0f, -2.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createTextButton(SGXSingCorrectConfigsPage::instance, "save changes", &SGXSingCorrectConfigsPage::confirmChanges, 0.5f, 0.0f, 1.0f, -2.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createTitle(bg, "SingCorrect configs", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 2.0f);
    SGXQuickUIInterface::createRightText(bg, "use SingCorrect?", 0.5f, -5.6f, 0.0f, 3.0f, 0.0f, 5.5f, 0.0f, 1.0f);
    SGXSingCorrectConfigsPage::enableButton = SGXQuickUIInterface::createTextButton(bg, "yes", &SGXSingCorrectConfigsPage::enableModule, 0.5f, 0.1f, 0.0f, 3.0f, 0.0f, 1.5f, 0.0f, 1.0f);
    SGXSingCorrectConfigsPage::disableButton = SGXQuickUIInterface::createTextButton(bg, "no", &SGXSingCorrectConfigsPage::disableModule, 0.5f, 1.7f, 0.0f, 3.0f, 0.0f, 1.5f, 0.0f, 1.0f);
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
}

void SGXSingCorrectConfigsPage::activate(){
    SGXQuickUIInterface::showPage(SGXSingCorrectConfigsPage::instance, &SGXSingCorrectConfigsPage::initialise, &SGXSingCorrectConfigsPage::reset);
}

void SGXSingCorrectConfigsPage::cancelChanges(){
    SGXSingCorrectCustomisation::loadFileData();
    SGXQuickUIInterface::hidePage(SGXSingCorrectConfigsPage::instance);
}

void SGXSingCorrectConfigsPage::confirmChanges(){
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
