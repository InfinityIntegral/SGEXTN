#include <private_api_Widgets/SGWLicensingInfoWindow.h>
#include <SGWBackground.h>
#include <SGWPageBackground.h>
#include <SGWWidget.h>
#include <SGWTextLabel.h>
#include <SGWHorizontalAlignment.h>
#include <SGWTextButton.h>
#include <SGWLongLabel.h>
#include <SGXFile.h>

SGWBackground* SGWLicensingInfoWindow::instance = nullptr;

SGWBackground* SGWLicensingInfoWindow::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    new SGWTextLabel(bg, "SGEXTN License (LGPL)", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.5f, SGWHorizontalAlignment::Center, false);
    new SGWLongLabel(bg, SGXFile::readAllText(":/SGEXTN/LICENSE.txt"), 0.0f, 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 1.0f, -3.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWTextButton(bg, "ok", &SGWLicensingInfoWindow::disable, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    return bg;
}

void SGWLicensingInfoWindow::activate(){
    SGWBackground::enable(SGWLicensingInfoWindow::instance, &SGWLicensingInfoWindow::initialise, nullptr);
}

void SGWLicensingInfoWindow::disable(){
    SGWBackground::disable(SGWLicensingInfoWindow::instance);
}
