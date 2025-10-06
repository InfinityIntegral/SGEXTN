#ifndef SGWFONTSIZECUSTOMISATIONPAGE_H
#define SGWFONTSIZECUSTOMISATIONPAGE_H

class SGWBackground;
class SGWButton;
class SGWLabel;
class SGWInput;
class SGWSingleTouchReceiver;
class SGWBlankWidget;
class SGXTouchEvent;
class SGWFontSizeCustomisationPage
{
public:
    SGWFontSizeCustomisationPage() = delete;
    static void activate();
    static SGWBackground* instance;
    static SGWBackground* initialise();
    static void reset();
    static SGWButton* exitButton;
    static void exit();
    static SGWInput* sizeInput;
    static SGWLabel* sizeInvalidMessage;
    static void sizeValidityCheck();
    static SGWLabel* sizeUnsavedMessage;
    static void sizeUnsavedCheck();
    static SGWSingleTouchReceiver* sliderInput;
    static SGWBlankWidget* sliderForeground;
    static void sliderChange(const SGXTouchEvent& x);
};

#endif // SGWFONTSIZECUSTOMISATIONPAGE_H
