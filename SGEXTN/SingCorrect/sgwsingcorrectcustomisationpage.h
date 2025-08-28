#ifndef SGWSINGCORRECTCUSTOMISATIONPAGE_H
#define SGWSINGCORRECTCUSTOMISATIONPAGE_H

template <typename T1, typename T2> class QHash;
class SGWBackground;
class SGWButton;
class SGWLabel;
class SGWInput;
class SGWWidget;
class QString;
class SGWSingCorrectCustomisationPage
{
public:
    SGWSingCorrectCustomisationPage() = delete;
    static SGWBackground* instance;
    static SGWBackground* initialise();
    static void activate();
    static void reset();
    static void exit(SGWButton* /*unused*/);
    static SGWButton* enableButton;
    static SGWButton* disableButton;
    static void enableFunction(SGWButton* /*unused*/);
    static void disableFunction(SGWButton* /*unused*/);
    static SGWInput* prefixInput;
    static SGWLabel* prefixInvalidMessage;
    static SGWLabel* prefixUnsavedMessage;
    static void prefixUpdated(SGWInput* /*unused*/);
    static void prefixSaved(SGWInput* /*unused*/);
    static SGWInput* customCharInput;
    static SGWInput* customCommandInput;
    static SGWLabel* customCharError;
    static SGWLabel* customCommandError;
    static void customCharCheck(SGWInput* /*unused*/);
    static void customCommandCheck(SGWInput* /*unused*/);
    static void addCustomCommand(SGWButton* /*unused*/);
    static void refreshList();
    static SGWWidget* listParent;
    static QHash<SGWButton*, QString>* buttonsList;
    static void deleteCommand(SGWButton* button);
    static SGWBackground* commandListInstance;
    static SGWBackground* initialiseCommandList();
    static void exitCommandList(SGWButton* /*unused*/);
    static void showCommandList(SGWButton* /*unused*/);
};

#endif // SGWSINGCORRECTCUSTOMISATIONPAGE_H
