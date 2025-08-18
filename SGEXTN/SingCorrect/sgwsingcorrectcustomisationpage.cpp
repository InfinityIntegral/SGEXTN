#include "sgwsingcorrectcustomisationpage.h"
#include "../widgets/sgwpagebackground.h"
#include "../widgets/sgwtextbutton.h"
#include "../widgets/sgwsequentialscrollview.h"
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwbutton.h"
#include "../widgets/sgwwidget.h"

SGWBackground* SGWSingCorrectCustomisationPage::instance = nullptr;
SGWBackground* SGWSingCorrectCustomisationPage::scroll = nullptr;
SGWButton* SGWSingCorrectCustomisationPage::exitButton = nullptr;

SGWBackground* SGWSingCorrectCustomisationPage::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 8);
    SGWSingCorrectCustomisationPage::scroll = new SGWSequentialScrollView(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8);
    SGWSingCorrectCustomisationPage::exitButton = new SGWTextButton(bg, "done", &SGWSingCorrectCustomisationPage::exit, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    return bg;
}

void SGWSingCorrectCustomisationPage::reset(){
    
}

void SGWSingCorrectCustomisationPage::activate(){
    SGWBackground::enable(SGWSingCorrectCustomisationPage::instance, &SGWSingCorrectCustomisationPage::initialise, &SGWSingCorrectCustomisationPage::reset);
}

void SGWSingCorrectCustomisationPage::exit(SGWButton */*unused*/){
    SGWBackground::disable(SGWSingCorrectCustomisationPage::instance);
}
