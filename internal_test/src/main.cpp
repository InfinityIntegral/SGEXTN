#include <iostream>
#include <private_api_Containers/SGLCrash.h>
#include <SGLArray.h>
#include <SGLIntLimits.h>
#include <SGLFloatMath.h>
#include <SGLFloatConstants.h>
#include <SGXCentral.h>
#include <QDebug>
#include <SGXIdentifier.h>
#include <SGXRandomNumberGenerator.h>
#include <SGXTimeStamp.h>
#include <SGXFileSystem.h>
#include <SGXFile.h>
#include <SGWBlankWidget.h>
#include <SGWTextButton.h>
#include <SGWTextInput.h>
#include <SGWTextLabel.h>
#include <SGWCustomisationPageControl.h>
#include <SGWColourPickerWidget.h>

#include <SGEXTN_EntryPoint.h>

void init();
void test();
void log();

int main(int argc, char** argv){
    return SGEXTN(argc, argv, &init);
}

void init(){
    SGXCentral::applicationName = "internal test";
    SGXCentral::applicationVersion = "v6.0.0";
    SGXCentral::organisationName = "05524F (Singapore)";
    SGXCentral::customInitialise = &test;
    SGXCentral::folderName = "SGEXTN";
}

void log(){
    qDebug() << "did something";
}

void test(){
    qDebug() << "Hello, Singapore";
    SGLArray<int> a(1, 2, 3, 4, 5);
    for(int i=0; i<a.length(); i++){
        qDebug() << a.at(i) << " ";
    };
    qDebug() << SGLIntLimits::maximum();
    qDebug() << SGLFloatMath::aToThePowerOfB(2.0f, 16.0f);
    qDebug() << SGLFloatConstants::eulerNumber();
    qDebug() << (*SGXIdentifier(false).getStringForPrinting().data);
    qDebug() << SGXRandomNumberGenerator::rng0To1();
    qDebug() << (*SGXTimeStamp::now().getString().data);
    qDebug() << (*SGXFileSystem::userDataFilePath.data);
    qDebug() << SGXFileSystem::getFolderSize(SGXFileSystem::configFilePath);
    if(SGXFileSystem::fileExists(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt")) == true){
        SGXFile fileReader(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt"));
        SGXString x = fileReader.readString();
        qDebug() << (*x.data);
    }
    {
        if(SGXFileSystem::fileExists(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt")) == false){SGXFileSystem::createFile(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt"));}
        SGXFile fileWriter(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt"));
        if(fileWriter.isValid == true){fileWriter.writeString(SGXTimeStamp::now().getString());}
    }
    SGWWidget* w = new SGWBlankWidget(SGWWidget::parentWidget, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 1.0f, -1.0f, 6);
    new SGWTextLabel(w, "built with CMake", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
    new SGWTextButton(w, "click here", &log, 0.0f, 0.5f, 0.0f, 2.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextInput(w, &log, 0.0f, 0.5f, 0.0f, 3.5f, 1.0f, -1.0f, 0.0f, 1.0f);
    //SGWCustomisationPageControl::enableThemeColoursCustomisationPage();
    new SGWColourPickerWidget(w, 0.0f, 0.5f, 0.0f, 5.0f, 0.0f, 4.0f, 0.0f, 1.0f, SGXColourRGBA(255, 0, 200, 200));
}
