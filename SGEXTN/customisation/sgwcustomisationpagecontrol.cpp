#include "sgwcustomisationpagecontrol.h"
#include "../SingCorrect/sgwsingcorrectcustomisationpage.h"
#include "../template/sgwfontsizecustomisationpage.h"
#include "../template/sgwthemecustomisationpage.h"

void SGWCustomisationPageControl::enableThemeColoursCustomisationPage(){
    SGWThemeCustomisationPage::activate();
}

void SGWCustomisationPageControl::enableFontSizeCustomisationPage(){
    SGWFontSizeCustomisationPage::activate();
}

void SGWCustomisationPageControl::enableSingCorrectCustomisationPage(){
    SGWSingCorrectCustomisationPage::activate();
}
