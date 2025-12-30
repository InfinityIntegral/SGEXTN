#include <SGLArray.h>
#include <SGLIntLimits.h>
#include <SGLFloatMath.h>
#include <SGLFloatConstants.h>
#include <SGXCentral.h>
#include <SGXIdentifier.h>
#include <SGXRandomNumberGenerator.h>
#include <SGXTimeStamp.h>
#include <SGXFileSystem.h>
#include <SGXFile.h>
#include <SGWBlankWidget.h>
#include <SGWTextButton.h>
#include <SGWTextInput.h>
#include <SGWTextLabel.h>
#include <SGWColourPickerWidget.h>
#include <SGWNotify.h>
#include <SGXDebug.h>
#include <SGWHorizontalAlignment.h>

#include <SGEXTN_EntryPoint.h>

namespace {
void logSomething(){
    SG("did something");
}

void test(){
    SG("Hello, Singapore");
    SGLArray<int> a(1, 2, 3, 4, 5);
    SGXString arrayContents = "";
    for(int i=0; i<a.length(); i++){
        arrayContents += (SGXString::intToString(a.at(i)) + " ");
    };
    SG(arrayContents);
    SG(SGLIntLimits::maximum());
    SG(SGLFloatMath::aToThePowerOfB(2.0f, 16.0f));
    SG(SGLFloatConstants::eulerNumber());
    SG(SGXIdentifier(false).getStringForPrinting());
    SG(SGXRandomNumberGenerator::rng0To1());
    SG(SGXTimeStamp::now().getString());
    SG(SGXFileSystem::userDataFilePath);
    SG(SGXFileSystem::getFolderSize(SGXFileSystem::configFilePath));
    if(SGXFileSystem::fileExists(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt")) == true){
        const SGXFile fileReader(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt"), SGXFile::ReadOnly);
        SG(fileReader.readString());
    }
    {
        if(SGXFileSystem::fileExists(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt")) == false){SGXFileSystem::createFile(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt"));}
        const SGXFile fileWriter(SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "testing.txt"), SGXFile::WriteOnly);
        if(fileWriter.openStatus == SGXFile::WriteOnly){fileWriter.writeString(SGXTimeStamp::now().getString());}
    }
    SGWWidget* w = new SGWBlankWidget(SGWWidget::parentWidget, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 1.0f, -1.0f, 6);
    new SGWTextLabel(w, "built with CMake", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
    new SGWTextButton(w, "click here", &logSomething, 0.0f, 0.5f, 0.0f, 2.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextInput(w, &logSomething, 0.0f, 0.5f, 0.0f, 3.5f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWColourPickerWidget(w, 0.0f, 0.5f, 0.0f, 5.0f, 0.0f, 4.0f, 0.0f, 1.0f, SGXColourRGBA(255, 0, 200, 200));
    SGWNotify::notify("something");
    SG(true)(1)("hi")(SGXColourRGBA(255, 0, 200, 200))(w)(SGXIdentifier(false));
    SG;
    const SGXString textPath = SGXFileSystem::joinFilePaths(SGXFileSystem::configFilePath, "text.txt");
    if(SGXFileSystem::fileExists(textPath)){SG(SGXFile::readAllText(textPath));}
    SGXFile::writeAllText(textPath, SGXTimeStamp::now().getString());
}

void init(){
    SGXCentral::applicationName = "internal test";
    SGXCentral::applicationVersion = "v6.2.0";
    SGXCentral::organisationName = "05524F (Singapore)";
    SGXCentral::customInitialise = &test;
    SGXCentral::folderName = "SGEXTN";
    SGXCentral::infoWebsite = "infinityintegral.github.io/SGEXTN/readme/readme";
}
}

int main(int argc, char** argv){
    return SGEXTN(argc, argv, &init);
}
