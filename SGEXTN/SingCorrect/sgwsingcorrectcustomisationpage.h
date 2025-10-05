#ifndef SGWSINGCORRECTCUSTOMISATIONPAGE_H
#define SGWSINGCORRECTCUSTOMISATIONPAGE_H

class SGWBackground;
class SGWButton;
class SGWLabel;
class SGWInput;
class SGWWidget;
class SGXString;
class SGWSingCorrectCustomisationPage
{
public:
    SGWSingCorrectCustomisationPage() = delete;
    static SGWBackground* instance;
    static SGWBackground* initialise();
    static void activate();
    static void reset();
    static void exit();
    static SGWButton* enableButton;
    static SGWButton* disableButton;
    static void enableFunction();
    static void disableFunction();
    static SGWInput* prefixInput;
    static SGWLabel* prefixInvalidMessage;
    static SGWLabel* prefixUnsavedMessage;
    static void prefixUpdated();
    static void prefixSaved();
    static SGWInput* customCharInput;
    static SGWInput* customCommandInput;
    static SGWLabel* customCharError;
    static SGWLabel* customCommandError;
    static void customCharCheck();
    static void customCommandCheck();
    static void addCustomCommand();
    static void refreshList();
    static SGWWidget* listParent;
    static void deleteCommand(const SGXString& customKey);
    static SGWBackground* commandListInstance;
    static SGWBackground* initialiseCommandList();
    static void exitCommandList();
    static void showCommandList();
};

#endif // SGWSINGCORRECTCUSTOMISATIONPAGE_H
