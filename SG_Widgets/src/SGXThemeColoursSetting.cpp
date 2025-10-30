#include <private_api_Widgets/SGXThemeColourSetting.h>
#include <SGXColourRGBA.h>
#include <QColor>
#include <SGXThemeColoursCustomisation.h>

namespace {
inline QColor temp_getQColour(SGXColourRGBA x){
    return QColor(x.getRed(), x.getGreen(), x.getBlue(), x.getTransparency());
}
}

SGXThemeColourSetting::SGXThemeColourSetting(){
    (*this).noColour = SGXColourRGBA(255, 255, 255, 0);
    (*this).themeColour0 = SGXThemeColoursCustomisation::themeColour0;
    (*this).themeColour1 = SGXThemeColoursCustomisation::themeColour1;
    (*this).themeColour2 = SGXThemeColoursCustomisation::themeColour2;
    (*this).themeColour3 = SGXThemeColoursCustomisation::themeColour3;
    (*this).themeColour4 = SGXThemeColoursCustomisation::themeColour4;
    (*this).themeColour5 = SGXThemeColoursCustomisation::themeColour5;
    (*this).themeColour6 = SGXThemeColoursCustomisation::themeColour6;
    (*this).themeColour7 = SGXThemeColoursCustomisation::themeColour7;
    (*this).themeColour8 = SGXThemeColoursCustomisation::themeColour8;
}

QColor SGXThemeColourSetting::getNoColour() const {
    return temp_getQColour(noColour);
}

QColor SGXThemeColourSetting::getThemeColour(int x) const {
    if(x == 0){return getThemeColour0();}
    if(x == 1){return getThemeColour1();}
    if(x == 2){return getThemeColour2();}
    if(x == 3){return getThemeColour3();}
    if(x == 4){return getThemeColour4();}
    if(x == 5){return getThemeColour5();}
    if(x == 6){return getThemeColour6();}
    if(x == 7){return getThemeColour7();}
    if(x == 8){return getThemeColour8();}
    return getNoColour();
}

QColor SGXThemeColourSetting::getThemeColour0() const {
    return temp_getQColour(themeColour0);
}

void SGXThemeColourSetting::setThemeColour0(const QColor &x){
    (*this).themeColour0 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour0();
}

QColor SGXThemeColourSetting::getThemeColour1() const {
    return temp_getQColour(themeColour1);
}

void SGXThemeColourSetting::setThemeColour1(const QColor &x){
    (*this).themeColour1 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour1();
}

QColor SGXThemeColourSetting::getThemeColour2() const {
    return temp_getQColour(themeColour2);
}

void SGXThemeColourSetting::setThemeColour2(const QColor &x){
    (*this).themeColour2 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour2();
}

QColor SGXThemeColourSetting::getThemeColour3() const {
    return temp_getQColour(themeColour3);
}

void SGXThemeColourSetting::setThemeColour3(const QColor &x){
    (*this).themeColour3 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour3();
}

QColor SGXThemeColourSetting::getThemeColour4() const {
    return temp_getQColour(themeColour4);
}

void SGXThemeColourSetting::setThemeColour4(const QColor &x){
    (*this).themeColour4 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour4();
}

QColor SGXThemeColourSetting::getThemeColour5() const {
    return temp_getQColour(themeColour5);
}

void SGXThemeColourSetting::setThemeColour5(const QColor &x){
    (*this).themeColour5 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour5();
}

QColor SGXThemeColourSetting::getThemeColour6() const {
    return temp_getQColour(themeColour6);
}

void SGXThemeColourSetting::setThemeColour6(const QColor &x){
    (*this).themeColour6 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour6();
}

QColor SGXThemeColourSetting::getThemeColour7() const {
    return temp_getQColour(themeColour7);
}

void SGXThemeColourSetting::setThemeColour7(const QColor &x){
    (*this).themeColour7 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour7();
}

QColor SGXThemeColourSetting::getThemeColour8() const {
    return temp_getQColour(themeColour8);
}

void SGXThemeColourSetting::setThemeColour8(const QColor &x){
    (*this).themeColour8 = SGXColourRGBA(x.red(), x.green(), x.blue(), x.alpha());
    (*this).changedThemeColour8();
}
