#include <private_api_Widgets/SGWConfigsWindow.h>
#include <SGWBackground.h>
#include <SGWPageBackground.h>
#include <SGWWidget.h>
#include <SGWTextLabel.h>
#include <SGWTextButton.h>
#include <SGWHorizontalAlignment.h>
#include <private_api_Widgets/SGWBasicThemeCustomisationPage.h>
#include <private_api_Widgets/SGWFontSizeCustomisationPage.h>
#include <private_api_Widgets/SGWSingCorrectCustomisationPage.h>
#include <SGXFileSystem.h>
#include <SGXCentral.h>
#include <SGWScrollView.h>

SGWBackground* SGWConfigsWindow::instance = nullptr;

SGWBackground* SGWConfigsWindow::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 8);
    new SGWTextLabel(bg, "SGEXTN configs", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.5f, SGWHorizontalAlignment::Center, false);
    SGWWidget* sv = new SGWScrollView(bg, 0.0f, 0.0f, 0.0f, 2.5f, 1.0f, 0.0f, 1.0f, -3.5f, 0.0f, 8.5f, 0.0f, 0.5f, 8);
    new SGWTextButton(sv, "change theme", &SGWBasicThemeCustomisationPage::activate, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextButton(sv, "change font size", &SGWFontSizeCustomisationPage::activate, 0.0f, 0.5f, 0.0f, 1.5f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextButton(sv, "configure SingCorrect", &SGWSingCorrectCustomisationPage::activate, 0.0f, 0.5f, 0.0f, 3.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextButton(sv, "view 05524F website", &SGWConfigsWindow::view05524FHomePage, 0.0f, 0.5f, 0.0f, 4.5f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextButton(sv, "view SGEXTN website", &SGWConfigsWindow::viewSGEXTNPage, 0.0f, 0.5f, 0.0f, 6.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    if(SGXCentral::infoWebsite != ""){new SGWTextButton(sv, "view app info website", &SGWConfigsWindow::viewApplicationInfoPage, 0.0f, 0.5f, 0.0f, 7.5f, 1.0f, -1.0f, 0.0f, 1.0f);}
    new SGWTextButton(bg, "done", &SGWConfigsWindow::disable, 0.0f, 0.5f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    return bg;
}

void SGWConfigsWindow::activate(){
    SGWBackground::enable(SGWConfigsWindow::instance, &SGWConfigsWindow::initialise, nullptr);
}

void SGWConfigsWindow::disable(){
    SGWBackground::disable(SGWConfigsWindow::instance);
}

void SGWConfigsWindow::view05524FHomePage(){
    SGXFileSystem::openLink("infinityintegral.github.io");
}

void SGWConfigsWindow::viewSGEXTNPage(){
    SGXFileSystem::openLink("infinityintegral.github.io/SGEXTN/readme/readme");
}

void SGWConfigsWindow::viewApplicationInfoPage(){
    SGXFileSystem::openLink(SGXCentral::infoWebsite);
}
