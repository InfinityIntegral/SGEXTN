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

void init();
void test();

int main(int argc, char** argv){
    (void)argc;
    (void)argv;
    SGEXTN(argc, argv, &init);
}

void init(){
    SGXCentral::applicationName = "internal test";
    SGXCentral::applicationVersion = "v6.0.0";
    SGXCentral::organisationName = "05524F (Singapore)";
    SGXCentral::customInitialise = &test;
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
}
