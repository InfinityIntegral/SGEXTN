#include <SGEXTN_EntryPoint.h>
#include <SGXCentral.h>
#include <SGWScrollView.h>
#include <SGWBlankWidget.h>
#include <SGWColourPickerWidget.h>
#include <SGWIconButton.h>
#include <SGWIconLabel.h>
#include <SGWLongInput.h>
#include <SGWLongLabel.h>
#include <SGWPageBackground.h>
#include <SGWSequentialScrollView.h>
#include <SGWSequentialLongLabel.h>
#include <SGWTextButton.h>
#include <SGWTextInput.h>
#include <SGWTextLabel.h>
#include <SGRRendererWidget.h>
#include <private_api_RI/SGRTransparencyIndicatorRenderer.h>

namespace {
void test(){
    SGWWidget* bg = new SGWScrollView(SGWWidget::parentWidget, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 25.0f, 0.0f, 0.5f);
    new SGWBlankWidget(bg, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f);
    new SGWColourPickerWidget(bg, 0.0f, 2.0f, 0.0f, 0.5f, 0.0f, 4.0f, 0.0f, 1.0f, SGXColourRGBA(255, 0, 200, 200));
    new SGWIconLabel(bg, 'A', 0.0f, 6.5f, 0.0f, 0.5f, 0.0f, 1.5f);
    new SGWIconButton(bg, 'A', nullptr, 0.0f, 8.5f, 0.0f, 0.5f, 0.0f, 1.5f);
    new SGWLongInput(bg, "Enter text here....", nullptr, 0.0f, 0.5f, 0.0f, 2.5f, 1.0f, -1.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    new SGWLongLabel(bg, "testing...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\n", 0.0f, 0.5f, 0.0f, 6.0f, 0.0f, 5.0f, 0.0f, 4.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWPageBackground(bg, 0.0f, 5.5f, 0.0f, 6.5f, 0.0f, 1.0f, 0.0f, 1.0f);
    SGWWidget* sbg = new SGWSequentialScrollView(bg, 0.0f, 0.5f, 0.0f, 10.0f, 1.0f, -1.0f, 0.0f, 4.0f, 0.0f, 0.5f);
    new SGWSequentialLongLabel(sbg, "testing...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\ntesting...\ntesting\n", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextButton(bg, "testing...", nullptr, 0.0f, 0.5f, 0.0f, 14.5f, 0.0f, 5.0f, 0.0f, 1.0f);
    new SGWTextInput(bg, "Enter text...", nullptr, 0.0f, 0.5f, 0.0f, 16.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextLabel(bg, "testing...", 0.0f, 0.5f, 0.0f, 17.5f, 0.0f, 5.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    new SGRRendererWidget(bg, 0.0f, 0.5f, 0.0f, 20.0f, 0.0f, 4.0f, 0.0f, 1.0f, new SGRTransparencyIndicatorRenderer(), nullptr);
}

void init(){
    SGXCentral::applicationName = "internal test";
    SGXCentral::applicationVersion = "v6.3.0";
    SGXCentral::organisationName = "05524F (Singapore)";
    SGXCentral::customInitialise = &test;
    SGXCentral::folderName = "SGEXTN";
}
}

int main(int argc, char** argv){
    return SGEXTN(argc, argv, &init);
}
