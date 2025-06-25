#include "sgxthemecoloursetting.h"
#include <QQmlEngine>
#include "../primitives/sgxcolourrgba.h"
#include <QObject>
#include <QJSEngine>
#include <QColor>
#include <qtmetamacros.h>
#include <qtpreprocessorsupport.h>

SGXThemeColourSetting::SGXThemeColourSetting(){
    (*this).noColour = SGXColourRGBA(255, 255, 255, 0);
    (*this).themeColour0 = SGXColourRGBA(0, 0, 0);
    (*this).themeColour1 = SGXColourRGBA(64, 0, 50);
    (*this).themeColour2 = SGXColourRGBA(128, 0, 100);
    (*this).themeColour3 = SGXColourRGBA(192, 0, 150);
    (*this).themeColour4 = SGXColourRGBA(255, 0, 200);
    (*this).themeColour5 = SGXColourRGBA(255, 64, 214);
    (*this).themeColour6 = SGXColourRGBA(255, 128, 228);
    (*this).themeColour7 = SGXColourRGBA(255, 192, 242);
    (*this).themeColour8 = SGXColourRGBA(255, 255, 255);
}

QObject* SGXThemeColourSetting::getObject(QQmlEngine *me, QJSEngine *se){
    Q_UNUSED(me);
    Q_UNUSED(se);
    return new SGXThemeColourSetting();
}

QColor SGXThemeColourSetting::getNoColour() const {
    return noColour.getQColour();
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
    return themeColour0.getQColour();
}

void SGXThemeColourSetting::setThemeColour0(const QColor &x){
    (*this).themeColour0 = SGXColourRGBA(x);
    emit (*this).changedThemeColour0();
}

QColor SGXThemeColourSetting::getThemeColour1() const {
    return themeColour1.getQColour();
}

void SGXThemeColourSetting::setThemeColour1(const QColor &x){
    (*this).themeColour1 = SGXColourRGBA(x);
    emit (*this).changedThemeColour1();
}

QColor SGXThemeColourSetting::getThemeColour2() const {
    return themeColour2.getQColour();
}

void SGXThemeColourSetting::setThemeColour2(const QColor &x){
    (*this).themeColour2 = SGXColourRGBA(x);
    emit (*this).changedThemeColour2();
}

QColor SGXThemeColourSetting::getThemeColour3() const {
    return themeColour3.getQColour();
}

void SGXThemeColourSetting::setThemeColour3(const QColor &x){
    (*this).themeColour3 = SGXColourRGBA(x);
    emit (*this).changedThemeColour3();
}

QColor SGXThemeColourSetting::getThemeColour4() const {
    return themeColour4.getQColour();
}

void SGXThemeColourSetting::setThemeColour4(const QColor &x){
    (*this).themeColour4 = SGXColourRGBA(x);
    emit (*this).changedThemeColour4();
}

QColor SGXThemeColourSetting::getThemeColour5() const {
    return themeColour5.getQColour();
}

void SGXThemeColourSetting::setThemeColour5(const QColor &x){
    (*this).themeColour5 = SGXColourRGBA(x);
    emit (*this).changedThemeColour5();
}

QColor SGXThemeColourSetting::getThemeColour6() const {
    return themeColour6.getQColour();
}

void SGXThemeColourSetting::setThemeColour6(const QColor &x){
    (*this).themeColour6 = SGXColourRGBA(x);
    emit (*this).changedThemeColour6();
}

QColor SGXThemeColourSetting::getThemeColour7() const {
    return themeColour7.getQColour();
}

void SGXThemeColourSetting::setThemeColour7(const QColor &x){
    (*this).themeColour7 = SGXColourRGBA(x);
    emit (*this).changedThemeColour7();
}

QColor SGXThemeColourSetting::getThemeColour8() const {
    return themeColour8.getQColour();
}

void SGXThemeColourSetting::setThemeColour8(const QColor &x){
    (*this).themeColour8 = SGXColourRGBA(x);
    emit (*this).changedThemeColour8();
}
