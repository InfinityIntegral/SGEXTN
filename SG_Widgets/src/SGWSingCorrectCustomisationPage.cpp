#include <private_api_Widgets/SGWSingCorrectCustomisationPage.h>
#include <private_api_Widgets/SGXSingCorrectCustomisation.h>
#include <SGXString.h>
#include <SGXSingCorrectCore.h>
#include <SGLUnorderedMap.h>
#include <SGLHash.h>
#include <SGLEqualsTo.h>
#include <SGWLongLabel.h>
#include <SGWPageBackground.h>
#include <SGWTextButton.h>
#include <SGWSequentialScrollView.h>
#include <SGWBackground.h>
#include <SGWButton.h>
#include <SGWWidget.h>
#include <SGWTextLabel.h>
#include <SGWBlankWidget.h>
#include <SGWHorizontalAlignment.h>
#include <SGWSequentialLongLabel.h>
#include <SGWTextInput.h>
#include <SGWInput.h>
#include <SGWLabel.h>
#include <SGWNotify.h>
#include <SGXChar.h>
#include <SGLArray.h>

SGWBackground* SGWSingCorrectCustomisationPage::instance = nullptr;
SGWButton* SGWSingCorrectCustomisationPage::enableButton = nullptr;
SGWButton* SGWSingCorrectCustomisationPage::disableButton = nullptr;
SGWInput* SGWSingCorrectCustomisationPage::prefixInput = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::prefixInvalidMessage = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::prefixUnsavedMessage = nullptr;
SGWInput* SGWSingCorrectCustomisationPage::customCharInput = nullptr;
SGWInput* SGWSingCorrectCustomisationPage::customCommandInput = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::customCharError = nullptr;
SGWLabel* SGWSingCorrectCustomisationPage::customCommandError = nullptr;
SGWWidget* SGWSingCorrectCustomisationPage::listParent = nullptr;
SGWBackground* SGWSingCorrectCustomisationPage::commandListInstance = nullptr;

SGWBackground* SGWSingCorrectCustomisationPage::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    SGWWidget* x = new SGWSequentialScrollView(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "SingCorrect configs", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, SGWHorizontalAlignment::Center, false);
    SGXString s = "    SingCorrect is a module builtin to SGEXTN that allows you to type special characters, including mathematical and scientific symbols, superscripts and subscripts, Optical Answer Sheet bubbles, and emojis in any SGEXTN input field. This is done by inputting LaTeX style commands, but the prefix is not fixed at \\, instead it is user-configurable and default set to SG-\\. After entering the command, press space to show the symbol.\n    This page is used to configure SingCorrect. Changes are applied immediately and can be verified in the input field provided below. (Try to enter: SG-\\SGhome )";
    new SGWSequentialLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextInput(x, nullptr, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWTextButton(x, "builtin command list", &SGWSingCorrectCustomisationPage::showCommandList, 0.5f, -4.0f, 0.0f, 0.0f, 0.0f, 8.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    SGWWidget* p = new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.5f);
    new SGWTextLabel(p, "use SingCorrect?", 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, -0.1f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWSingCorrectCustomisationPage::enableButton = new SGWTextButton(p, "yes", &SGWSingCorrectCustomisationPage::enableFunction, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGWSingCorrectCustomisationPage::disableButton = new SGWTextButton(p, "no", &SGWSingCorrectCustomisationPage::disableFunction, 0.5f, 2.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    s = "    The prefix, default being SG-\\, determines what text is recognised as SingCorrect commands. Use the prefix \\ for similarity to LaTeX.";
    new SGWSequentialLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f);
    new SGWTextLabel(p, "prefix:", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWSingCorrectCustomisationPage::prefixInput = new SGWTextInput(p, &SGWSingCorrectCustomisationPage::prefixSaved, 0.0f, 2.1f, 0.0f, 0.0f, 1.0f, -2.1f, 0.0f, 1.0f);
    (*SGWSingCorrectCustomisationPage::prefixInput).textChangedFunction = (&SGWSingCorrectCustomisationPage::prefixUpdated);
    SGWSingCorrectCustomisationPage::prefixInvalidMessage = new SGWTextLabel(p, "prefix cannot be blank", 0.0f, 2.1f, 0.0f, 1.0f, 1.0f, -2.1f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    SGWSingCorrectCustomisationPage::prefixUnsavedMessage = new SGWTextLabel(p, "press tab to save", 0.0f, 2.1f, 0.0f, 1.0f, 1.0f, -2.1f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    s = "    You can define custom SingCorrect commands that function exactly like builtin ones by entering the symbol (copy paste it from copychar.cc) and the command. Note that you can redefine a builtin command by defining a custom command with the same name.";
    new SGWSequentialLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 3.0f);
    new SGWTextLabel(p, "symbol", 0.25f, -2.6f, 0.0f, 0.0f, 0.0f, 2.5f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
    new SGWTextLabel(p, "command", 0.25f, 0.1f, 0.0f, 0.0f, 0.5f, -0.2f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
    SGWSingCorrectCustomisationPage::customCharInput = new SGWTextInput(p, &SGWSingCorrectCustomisationPage::customCharCheck, 0.25f, -2.6f, 0.0f, 1.0f, 0.0f, 2.5f, 0.0f, 1.0f);
    SGWSingCorrectCustomisationPage::customCommandInput = new SGWTextInput(p, &SGWSingCorrectCustomisationPage::customCommandCheck, 0.25f, 0.1f, 0.0f, 1.0f, 0.5f, 0.3f, 0.0f, 1.0f);
    new SGWTextButton(p, "add", &SGWSingCorrectCustomisationPage::addCustomCommand, 0.75f, 0.6f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGWSingCorrectCustomisationPage::customCharError = new SGWTextLabel(p, "single symbol", 0.25f, -2.1f, 0.0f, 2.0f, 0.0f, 4.0f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    SGWSingCorrectCustomisationPage::customCommandError = new SGWTextLabel(p, "only letters, not blank", 0.5f, -1.5f, 0.0f, 2.0f, 0.0f, 6.0f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    new SGWTextLabel(x, "custom SingCorrect commands:", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    SGWSingCorrectCustomisationPage::listParent = new SGWSequentialScrollView(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextButton(bg, "done", &SGWSingCorrectCustomisationPage::exit, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    return bg;
}

void SGWSingCorrectCustomisationPage::reset(){
    if(SGXSingCorrectCustomisation::moduleEnabled == true){
        (*SGWSingCorrectCustomisationPage::enableButton).setSelected(true);
        (*SGWSingCorrectCustomisationPage::disableButton).setSelected(false);
    }
    else{
        (*SGWSingCorrectCustomisationPage::enableButton).setSelected(false);
        (*SGWSingCorrectCustomisationPage::disableButton).setSelected(true);
    }
    (*SGWSingCorrectCustomisationPage::prefixInput).setTextFromString(SGXSingCorrectCore::correctionPrefix);
    (*SGWSingCorrectCustomisationPage::prefixUnsavedMessage).setItemVisibility(false);
    SGWSingCorrectCustomisationPage::refreshList();
}

void SGWSingCorrectCustomisationPage::activate(){
    SGWBackground::enable(SGWSingCorrectCustomisationPage::instance, &SGWSingCorrectCustomisationPage::initialise, &SGWSingCorrectCustomisationPage::reset);
}

void SGWSingCorrectCustomisationPage::exit(){
    SGWBackground::disable(SGWSingCorrectCustomisationPage::instance);
    SGXSingCorrectCustomisation::syncFileData();
    SGWNotify::notify("all changes saved");
}

void SGWSingCorrectCustomisationPage::enableFunction(){
    SGXSingCorrectCustomisation::moduleEnabled = true;
    (*SGWSingCorrectCustomisationPage::enableButton).setSelected(true);
    (*SGWSingCorrectCustomisationPage::disableButton).setSelected(false);
}

void SGWSingCorrectCustomisationPage::disableFunction(){
    SGXSingCorrectCustomisation::moduleEnabled = false;
    (*SGWSingCorrectCustomisationPage::enableButton).setSelected(false);
    (*SGWSingCorrectCustomisationPage::disableButton).setSelected(true);
}

void SGWSingCorrectCustomisationPage::prefixUpdated(){
    (*SGWSingCorrectCustomisationPage::prefixUnsavedMessage).setItemVisibility(true);
}

void SGWSingCorrectCustomisationPage::prefixSaved(){
    (*SGWSingCorrectCustomisationPage::prefixUnsavedMessage).setItemVisibility(false);
    const SGXString prefix = (*SGWSingCorrectCustomisationPage::prefixInput).getTextAsString();
    if(prefix == ""){
        (*SGWSingCorrectCustomisationPage::prefixInvalidMessage).setItemVisibility(true);
        (*SGWSingCorrectCustomisationPage::prefixInput).setInvalid(true);
        return;
    }
    (*SGWSingCorrectCustomisationPage::prefixInvalidMessage).setItemVisibility(false);
    (*SGWSingCorrectCustomisationPage::prefixInput).setInvalid(false);
    SGXSingCorrectCore::correctionPrefix = prefix;
}

void SGWSingCorrectCustomisationPage::customCharCheck(){
    const SGXString s = (*SGWSingCorrectCustomisationPage::customCharInput).getTextAsString();
    if(s.length() != 1){
        (*SGWSingCorrectCustomisationPage::customCharInput).setInvalid(true);
        (*SGWSingCorrectCustomisationPage::customCharError).setItemVisibility(true);
    }
    else{
        (*SGWSingCorrectCustomisationPage::customCharInput).setInvalid(false);
        (*SGWSingCorrectCustomisationPage::customCharError).setItemVisibility(false);
    }
}

void SGWSingCorrectCustomisationPage::customCommandCheck(){
    const SGXString s = (*SGWSingCorrectCustomisationPage::customCommandInput).getTextAsString();
    bool isValid = true;
    for(int i=0; i<s.length(); i++){
        if(s.at(i).isEnglishLetter() == false){isValid = false;}
    }
    if(s == ""){isValid = false;}
    if(isValid == false){
        (*SGWSingCorrectCustomisationPage::customCommandInput).setInvalid(true);
        (*SGWSingCorrectCustomisationPage::customCommandError).setItemVisibility(true);
    }
    else{
        (*SGWSingCorrectCustomisationPage::customCommandInput).setInvalid(false);
        (*SGWSingCorrectCustomisationPage::customCommandError).setItemVisibility(false);
    }
}

void SGWSingCorrectCustomisationPage::addCustomCommand(){
    const SGXString c = (*SGWSingCorrectCustomisationPage::customCharInput).getTextAsString();
    const SGXString s = (*SGWSingCorrectCustomisationPage::customCommandInput).getTextAsString();
    bool isValid = true;
    if(c.length() != 1){isValid = false;}
    for(int i=0; i<s.length(); i++){
        if(s.at(i).isEnglishLetter() == false){isValid = false;}
    }
    if(s == ""){isValid = false;}
    if(isValid == false){
        SGWNotify::pullDownNotify("invalid command");
        return;
    }
    if((*SGXSingCorrectCustomisation::database).contains(s) == true){
        SGWNotify::pullDownNotify("command already exists");
        return;
    }
    (*SGXSingCorrectCustomisation::database).insert(s, c.at(0));
    (*SGWSingCorrectCustomisationPage::customCharInput).setTextFromString("");
    (*SGWSingCorrectCustomisationPage::customCommandInput).setTextFromString("");
    (*SGWSingCorrectCustomisationPage::customCharInput).setInvalid(false);
    (*SGWSingCorrectCustomisationPage::customCommandInput).setInvalid(false);
    (*SGWSingCorrectCustomisationPage::customCharError).setItemVisibility(false);
    (*SGWSingCorrectCustomisationPage::customCommandError).setItemVisibility(false);
    SGWSingCorrectCustomisationPage::refreshList();
}

void SGWSingCorrectCustomisationPage::refreshList(){
    const SGLArray<SGWWidget*> c = (*SGWSingCorrectCustomisationPage::listParent).getChildren();
    for(int i=0; i<c.length(); i++){
        (*c.at(i)).deleteWidget();
    }
    for(SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>::ConstIterator i = (*SGXSingCorrectCustomisation::database).constBegin(); i != (*SGXSingCorrectCustomisation::database).constEnd(); i++){
        SGWWidget* x = new SGWBlankWidget(SGWSingCorrectCustomisationPage::listParent, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
        new SGWTextLabel(x, i.value(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
        new SGWTextLabel(x, i.key(), 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, -3.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
        SGWButton* b = new SGWTextButton(x, "x", nullptr, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
        (*b).attachedString = i.key();
        (*b).clickFunctionWithString = (&SGWSingCorrectCustomisationPage::deleteCommand);
    }
}

void SGWSingCorrectCustomisationPage::deleteCommand(const SGXString& customKey){
    (*SGXSingCorrectCustomisation::database).erase(customKey);
    SGWSingCorrectCustomisationPage::refreshList();
}

SGWBackground* SGWSingCorrectCustomisationPage::initialiseCommandList(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    SGWWidget* x = new SGWSequentialScrollView(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextButton(bg, "exit", &SGWSingCorrectCustomisationPage::exitCommandList, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    SGXString s = "    This page display builtin SingCorrect commands including those from LaTeX (using the KaTeX version which should be mostly compatible with AoPS). The commands are arranged in packages (as in LaTeX packages).";
    new SGWSequentialLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "SG mark", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u0378    SGhome");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX delimiters", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u0028    lparen\n\u0029    rparen\n\u005B    lbrack\n\u005D    rbrack\n\u007B    lbrace\n\u007D    rbrace\n\u27E8    langle\n\u27E9    rangle\n\u007C    vert\n\u2225    Vert\n\u007C    lvert\n\u007C    rvert\n\u2225    lVert\n\u2225    rVert\n\u27E8    lang\n\u27E9    rang\n\u003C    lt\n\u003E    gt\n\u2308    lceil\n\u2309    rceil\n\u230A    lfloor\n\u230B    rfloor\n\u0028    lgroup\n\u0029    lgroup\n\u231C    ulcorner\n\u231D    urcorner\n\u231E    llcorner\n\u231F    lrcorner\n\u27E6    llbracket\n\u27E7    rrbracket\n\u2191    uparrow\n\u2193    downarrow\n\u2195    updownarrow\n\u21D1    Uparrow\n\u21D3    Downarrow\n\u21D5    Updownarrow\n\u005C    backslash");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX Greek letters", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u0391    Alpha\n\u0392    Beta\n\u0393    Gamma\n\u0394    Delta\n\u0395    Epsilon\n\u0396    Zeta\n\u0397    Eta\n\u0398    Theta\n\u0399    Iota\n\u039A    Kappa\n\u039B    Lambda\n\u039C    Mu\n\u039D    Nu\n\u039E    Xi\n\u039F    Omicron\n\u03A0    Pi\n\u03A1    Rho\n\u03A3    Sigma\n\u03A4    Tau\n\u03A5    Upsilon\n\u03A6    Phi\n\u03A7    Chi\n\u03A8    Psi\n\u03A9    Omega\n\u03B1    alpha\n\u03B2    beta\n\u03B3    gamma\n\u03B4    delta\n\u03B5    epsilon\n\u03B6    zeta\n\u03B7    eta\n\u03B8    theta\n\u03B9    iota\n\u03BA    kappa\n\u03BB    lambda\n\u03BC    mu\n\u03BD    nu\n\u03BE    xi\n\u03BF    omicron\n\u03C0    pi\n\u03C1    rho\n\u03C3    sigma\n\u03C4    tau\n\u03C5    upsilon\n\u03C6    phi\n\u03C7    chi\n\u03C8    psi\n\u03C9    omega");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX other letters", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2135    aleph\n\u2135    alef\n\u2135    alefsym\n\u2136    beth\n\u2137    gimel\n\u2138    daleth\n\u2207    nabla\n\u2202    partial\n\u2102    cnums\n\u2102    Complex\n\u2113    ell\n\u210F    hbar\n\u210F    hslash\n\u2111    Im\n\u2111    image\n\u2115    N\n\u2115    natnums\n\u211D    R\n\u211C    Re\n\u211C    real\n\u211D    reals\n\u211D    Reals\n\u2118    wp\n\u2118    weierp\n\u2124    Z\n\u2205    o\n\u2205    O");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX logic & sets", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2200    forall\n\u2203    exists\n\u2203    exist\n\u2204    nexists\n\u2208    in\n\u2208    isin\n\u2209    notin\n\u2201    complement\n\u2282    subset\n\u2283    supset\n\u2223    mid\n\u2227    land\n\u2228    lor\n\u220B    ni\n\u2234    therefore\n\u2235    because\n\u21A6    mapsto\n\u2192    to\n\u2190    gets\n\u2194    leftrightarrow\n\u220C    notni\n\u2205    emptyset\n\u2205    empty\n\u2205    varnothing\n\u21D2    implies\n\u21D0    impliedby\n\u21D4    iff\n\u00AC    neg\n\u00AC    lnot");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX big operators", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2211    sum\n\u222B    int\n\u222C    iint\n\u222D    iiint\n\u222E    oint\n\u220F    prod\n\u2210    coprod\n\u222B    intop\n\u222B    smallint\n\u222F    oiint\n\u2297    bigotimes\n\u2295    bigoplus\n\u2299    bigodot\n\u228E    biguplus\n\u2230    oiiint\n\u22C1    bigvee\n\u22C0    bigwedge\n\u22C2    bigcap\n\u22C3    bigcup\n\u2294    bigsqcup");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX binary operators", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u002B    plus\n\u002D    minus\n\u002F    slash\n\u002A    asterisk\n\u0026    And\n\u002A    ast\n\u22BC    barwedge\n\u25CB    bigcirc\n\u22A1    boxdot\n\u229F    boxminus\n\u229E    boxplus\n\u22A0    boxtimes\n\u00B7    bullet\n\u22D2    Cap\n\u2229    cap\n\u00B7    cdot\n\u00B7    cdotp\n\u00B7    centerdot\n\u2218    circ\n\u229B    circledast\n\u229A    circledcirc\n\u229D    circleddash\n\u22D3    Cup\n\u222A    cup\n\u22CE    curlyvee\n\u22CF    curlywedge\n\u00F7    div\n\u22C7    divideontimes\n\u2214    dotplus\n\u2306    doublebarwedge\n\u22D2    doublecap\n\u22D3    doublecup\n\u22D7    gtrdot\n\u22BA    intercal\n\u2227    land\n\u22CB    leftthreetimes\n\u00B7    ldotp\n\u2228    lor\n\u22D6    lessdot\n\u22B2    lhd\n\u22C9    ltimes\n\u2213    mp\n\u2299    odot\n\u2296    ominus\n\u2295    oplus\n\u2297    otimes\n\u2298    oslash\n\u00B1    pm\n\u00B1    plusmn\n\u22B3    rhd\n\u22CC    rightthreetimes\n\u22CA    rtimes\n\u2216    setminus\n\u2216    smallsetminus\n\u2293    sqcap\n\u2294    sqcup\n\u00D7    times\n\u22B4    unlhd\n\u22B5    unrhd\n\u228E    uplus\n\u2228    vee\n\u22BB    veebar\n\u2227    wedge\n\u2240    wr\n\u221A    sqrt\n\u221B    cbrt\n\u221A    squareroot\n\u221B    cuberoot\n\u221C    fourthroot");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX relational operators", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u003D    equals\n\u003C    less\n\u003C    lessthan\n\u003E    greater\n\u003E    greaterthan\n\u003A    colon\n\u2248    approx\n\u224A    approxeq\n\u224D    asymp\n\u2208    backepsilon\n\u223D    backsim\n\u22CD    backsimeq\n\u226C    between\n\u22C8    bowtie\n\u224F    bumpeq\n\u224E    Bumpeq\n\u2257    circeq\n\u2254    coloneqq\n\u2254    colonequals\n\u2245    cong\n\u22DE    curlyeqprec\n\u22DF    curlyeqsucc\n\u22A3    dashv\n\u2237    dblcolon\n\u2237    coloncolon\n\u2250    doteg\n\u2251    Doteq\n\u2251    doteqdot\n\u2256    eqcirc\n\u2239    eqcolon\n\u2239    minuscolon\n\u2255    eqqcolon\n\u2255    equalscolon\n\u2242    eqsim\n\u22DD    eqslantgtr\n\u22DC    eqslantless\n\u2261    equiv\n\u2261    congruent\n\u2252    fallingdotseq\n\u2322    frown\n\u2265    ge\n\u2265    geq\n\u2267    geqq\n\u2265    geqslant\n\u226B    gg\n\u22D9    ggg\n\u22D9    gggtr\n\u003E    gt\n\u22DB    gtreqless\n\u2277    gtrless\n\u2273    gtrsim\n\u22B7    imageof\n\u2208    in\n\u2208    isin\n\u22C8    Join\n\u2264    le\n\u2264    leg\n\u2266    leqq\n\u2264    leqslant\n\u22DA    lesseqgtr\n\u2276    lessgtr\n\u2272    lesssim\n\u226A    ll\n\u22D8    lll\n\u22D8    llless\n\u003C    lt\n\u2223    mid\n\u22A8    models\n\u22B8    multimap\n\u22B6    origof\n\u220B    owns\n\u2225    parallel\n\u22A5    perp\n\u22A5    perpendicular\n\u22D4    pitchfork\n\u227A    prec\n\u227A    minorises\n\u227C    preccurlyeq\n\u227C    preceq\n\u227E    precsim\n\u221D    propto\n\u221D    proportional\n\u2253    risingdotseq\n\u2223    shortmid\n\u2225    shortparallel\n\u223C    sim\n\u2243    simeq\n\u2322    smallfrown\n\u2323    smallsmile\n\u2323    smile\n\u228F    sqsubset\n\u2291    sqsubseteq\n\u2290    sqsupset\n\u2292    sqsupseteq\n\u22D0    Subset\n\u2282    subset\n\u2282    sub\n\u2286    subseteq\n\u2286    sube\n\u227B    succ\n\u227B    majorises\n\u227D    succcurlyeq\n\u227D    succeq\n\u227F    succsim\n\u22D1    Supset\n\u2283    supset\n\u2287    supseteq\n\u2287    supe\n\u2248    thickapprox\n\u223C    thicksim\n\u22B4    trianglelefteq\n\u225C    triangleq\n\u22B5    trianglerighteq\n\u221D    varpropto\n\u2206    vartriangle\n\u22B2    vartriangleleft\n\u22B3    vartriangleright\n\u003A    vcentcolon\n\u003A    ratio\n\u22A6    vdash\n\u22A8    vDash\n\u22A9    Vdash\n\u22AA    Vvdash");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX negative relational operators", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2260    notequals\n\u2269    gneqq\n\u22E7    gnsim\n\u2269    gvertneqq\n\u2268    lneqq\n\u22E6    lnsim\n\u2268    lvertneqq\n\u2247    ncong\n\u2260    ne\n\u2260    neq\n\u2271    ngeq\n\u2271    ngeqslant\n\u226F    ngtr\n\u2270    nleq\n\u2270    nleqslant\n\u226E    nless\n\u2224    nmid\n\u2209    notin\n\u220C    notni\n\u2226    nparallel\n\u2280    nprec\n\u22E0    npreceq\n\u2224    nshortmid\n\u2226    nshortparallel\n\u2241    nsim\n\u2288    nsubseteq\n\u2281    nsucc\n\u22E1    nsucceq\n\u2289    nsupseteq\n\u22EA    ntriangleleft\n\u22EC    ntrianglelefteq\n\u22EB    ntriangleright\n\u22ED    ntrianglerighteq\n\u22AC    nvdash\n\u22AD    nvDash\n\u22AF    nVDash\n\u22AE    nVdash\n\u22E8    precnsim\n\u228A    subsetneq\n\u22E9    succnsim\n\u228B    supsetneq\n\u228A    varsubsetneq\n\u228B    varsupsetneq");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX arrows", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u21BA    circlearrowleft\n\u21BB    circlearrowright\n\u21B6    curvearrowleft\n\u21B7    curvearrowright\n\u21D3    Darr\n\u21D3    dArr\n\u2193    darr\n\u2193    downarrow\n\u21D3    Downarrow\n\u21C3    downharpoonleft\n\u21C2    downharpoonright\n\u2190    gets\n\u21D4    Harr\n\u21D4    hArr\n\u2194    harr\n\u21A9    hookleftarrow\n\u21AA    hookrightarrow\n\u27FA    iff\n\u27F8    impliedby\n\u27F9    implies\n\u21D0    Larr\n\u21D0    lArr\n\u2190    larr\n\u2190    leftarrow\n\u21D0    Leftarrow\n\u21A2    leftarrowtail\n\u21BD    leftharpoondown\n\u21BC    leftharpoonup\n\u2194    leftrightarrow\n\u21D4    Leftrightarrow\n\u21C6    leftrightarrows\n\u21CB    leftrightharpoons\n\u27F5    longleftarrow\n\u27F8    Longleftarrow\n\u27F7    longleftrightarrow\n\u27FA    Longleftrightarrow\n\u27FC    longmapsto\n\u27F6    longrightarrow\n\u27F9    Longrightarrow\n\u21D4    Lrarr\n\u21D4    lrArr\n\u2194    lrarr\n\u21B0    Lsh\n\u21A6    mapsto\n\u2197    nearrow\n\u219A    nleftarrow\n\u21CD    nLeftarrow\n\u21AE    nleftrightarrow\n\u21CE    nLeftrightarrow\n\u219B    nrightarrow\n\u21CF    nRightarrow\n\u2196    nwarrow\n\u21D2    Rarr\n\u21D2    rArr\n\u2192    rarr\n\u21BE    restriction\n\u2192    rightarrow\n\u21D2    Rightarrow\n\u21A3    rightarrowtail\n\u21C1    rightharpoondown\n\u21C0    rightharpoonup\n\u21C4    rightleftarrows\n\u21CC    rightleftharpoons\n\u21B1    Rsh\n\u2198    searrow\n\u2199    swarrow\n\u2192    to\n\u21D1    Uarr\n\u21D1    uArr\n\u2191    uarr\n\u2191    uparrow\n\u21D1    Uparrow\n\u2195    updownarrow\n\u21D5    Updownarrow\n\u21BF    upharpoonleft\n\u21BE    upharpoonright");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "LaTeX punctuation", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u0025    percent\n\u0023    hashtag\n\u0026    andsign\n\u0026    ampersand\n\u005F    underscore\n\u005F    textunderscore\n\u2013    endash\n\u2013    textendash\n\u2014    emdash\n\u2014    textemdash\n\u007E    tilde\n\u007E    asciitilde\n\u007E    textasciitilde\n\u007E    destructor\n\u005E    circum\n\u005E    asciicircum\n\u005E    textasciicircum\n\u005E    exponent\n\u0060    backtick\n\u2018    quoteleft\n\u2018    textquoteleft\n\u2018    lq\n\u2019    quoteright\n\u2019    textquoteright\n\u2019    rq\n\u201C    quotedoubleleft\n\u201C    quotedbleft\n\u201C    textquotedblleft\n\u201D    quotedoubleright\n\u201D    quotedblright\n\u201D    textquotedblright\n\u003A    colon\n\u2035    backprime\n\u2032    prime\n\u003C    less\n\u003C    textless\n\u003E    greater\n\u003E    textgreater\n\u007C    bar\n\u007C    textbar\n\u2225    bardbl\n\u2225    textbardbl\n\u007B    braceleft\n\u007B    textbraceleft\n\u007D    braceright\n\u007D    textbraceright\n\u005C    backslash\n\u005C    textbackslash\n\u00B6    P\n\u00A7    S\n\u00A7    sect\n\u00A9    copyright\n\u00AE    circledR\n\u00AE    registered\n\u00AE    textregistered\n\u2026    dots\n\u22EF    cdots\n\u22F1    ddots\n\u2026    ldots\n\u22EE    vdots\n\u22EF    dotsb\n\u2026    dotsc\n\u22EF    dotsi\n\u22EF    dotsm\n\u2026    dotso\n\u00B7    sdot\n\u2026    mathellipsis\n\u2026    textellipsis\n\u2026    ellipsis\n\u25A1    Box\n\u25A1    square\n\u25A0    blacksquare\n\u25B3    triangle\n\u25BD    triangledown\n\u25C1    triangleleft\n\u25B7    triangleright\n\u25BD    bigtriangledown\n\u25B3    bigtriangleup\n\u25B2    blacktriangle\n\u25BC    blacktriangledown\n\u25C0    blacktriangleleft\n\u25B6    blacktriangleright\n\u25C7    diamond\n\u25CA    Diamond\n\u25CA    lozenge\n\u2B27    blacklozenge\n\u2605    star\n\u2605    bigstar\n\u2207    nabla\n\u221E    infty\n\u221E    infin\n\u221E    infinity\n\u2611    checkmark\n\u2612    crossmark\n\u2610    blankmark\n\u2220    angle\n\u2221    measuredangle\n\u2222    sphericalangle\n\u22A4    top\n\u22A5    bot\n\u0024    dollar\n\u0024    textdollar\n\u00A5    yuan\n\u221A    surd\n\u00B0    degree\n\u00B0    textdegree\n\u2127    mho\n\u27CD    diagdown\n\u27CB    diagup\n\u2665    heart");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "superscripts", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2070    SGsupzero\n\u00B9    SGsupone\n\u00B2    SGsuptwo\n\u00B3    SGsupthree\n\u2074    SGsupfour\n\u2075    SGsupfive\n\u2076    SGsupsix\n\u2077    SGsupseven\n\u2078    SGsupeight\n\u2079    SGsupnine\n\u207A    SGsupplus\n\u207B    SGsupminus\n\u207D    SGsupleft\n\u207E    SGsupright\n\u207C    SGsupequals\n\u3200    SGsupA\n\u3201    SGsupB\n\u3202    SGsupC\n\u3203    SGsupD\n\u3204    SGsupE\n\u3205    SGsupF\n\u3206    SGsupG\n\u3207    SGsupH\n\u3208    SGsupI\n\u3209    SGsupJ\n\u320A    SGsupK\n\u320B    SGsupL\n\u320C    SGsupM\n\u320D    SGsupN\n\u320E    SGsupO\n\u320F    SGsupP\n\u3210    SGsupQ\n\u3211    SGsupR\n\u3212    SGsupS\n\u3213    SGsupT\n\u3214    SGsupU\n\u3215    SGsupV\n\u3216    SGsupW\n\u3217    SGsupX\n\u3218    SGsupY\n\u3219    SGsupZ\n\u3220    SGsupa\n\u3221    SGsupb\n\u3222    SGsupc\n\u3223    SGsupd\n\u3224    SGsupe\n\u3225    SGsupf\n\u3226    SGsupg\n\u3227    SGsuph\n\u3228    SGsupi\n\u3229    SGsupj\n\u322A    SGsupk\n\u322B    SGsupl\n\u322C    SGsupm\n\u322D    SGsupn\n\u322E    SGsupo\n\u322F    SGsupp\n\u3230    SGsupq\n\u3231    SGsupr\n\u3232    SGsups\n\u3233    SGsupt\n\u3234    SGsupu\n\u3235    SGsupv\n\u3236    SGsupw\n\u3237    SGsupx\n\u3238    SGsupy\n\u3239    SGsupz");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "subscripts", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2080    SGsubzero\n\u2081    SGsubone\n\u2082    SGsubtwo\n\u2083    SGsubthree\n\u2084    SGsubfour\n\u2085    SGsubfive\n\u2086    SGsubsix\n\u2087    SGsubseven\n\u2088    SGsubeight\n\u2089    SGsubnine\n\u208A    SGsubplus\n\u208B    SGsubminus\n\u208D    SGsubleft\n\u208E    SGsubright\n\u208C    SGsubequals\n\u3240    SGsubA\n\u3241    SGsubB\n\u3242    SGsubC\n\u3243    SGsubD\n\u3244    SGsubE\n\u3245    SGsubF\n\u3246    SGsubG\n\u3247    SGsubH\n\u3248    SGsubI\n\u3249    SGsubJ\n\u324A    SGsubK\n\u324B    SGsubL\n\u324C    SGsubM\n\u324D    SGsubN\n\u324E    SGsubO\n\u324F    SGsubP\n\u3250    SGsubQ\n\u3251    SGsubR\n\u3252    SGsubS\n\u3253    SGsubT\n\u3254    SGsubU\n\u3255    SGsubV\n\u3256    SGsubW\n\u3257    SGsubX\n\u3258    SGsubY\n\u3259    SGsubZ\n\u3260    SGsuba\n\u3261    SGsubb\n\u3262    SGsubc\n\u3263    SGsubd\n\u3264    SGsube\n\u3265    SGsubf\n\u3266    SGsubg\n\u3267    SGsubh\n\u3268    SGsubi\n\u3269    SGsubj\n\u326A    SGsubk\n\u326B    SGsubl\n\u326C    SGsubm\n\u326D    SGsubn\n\u326E    SGsubo\n\u326F    SGsubp\n\u3270    SGsubq\n\u3271    SGsubr\n\u3272    SGsubs\n\u3273    SGsubt\n\u3274    SGsubu\n\u3275    SGsubv\n\u3276    SGsubw\n\u3277    SGsubx\n\u3278    SGsuby\n\u3279    SGsubz");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "emojis", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2610    SGemojiblank\n\u2611    SGemojicorrect\n\u2612    SGemojiwrong\n\u2605    SGemojistar\n\u2665    SGemojiheart\n\u2BCE    SGemojifourstar\n\u2BCF    SGemojirotatedfourstar\n\u2BCC    SGemojifilledfourstar\n\u2BCD    SGemojirotatedfilledfourstar\n\u25FB    SGemojiqed\n\u25A7    SGemojirightshade\n\u25A8    SGemojileftshade\n\u25A4    SGemojihorizshade\n\u25A5    SGemojivertshade\n\u25A6    SGemojiaxisalignedshade\n\u25A9    SGemojidiagshade\n\u2003    SGemojinoshade\n\u2588    SGemojiallshade\n\u2591    SGemojilightshade\n\u2592    SGemojimediumshade\n\u2593    SGemojidarkshade\n\u25C1    SGemojilefttri\n\u25C0    SGemojifilledlefttri\n\u25B7    SGemojirighttri\n\u25B6    SGemojifilledrighttri\n\u25B3    SGemojiuptri\n\u25B2    SGemojifilleduptri\n\u25BD    SGemojidowntri\n\u25BC    SGemojifilleddowntri\n\u25A1    SGemojisquare\n\u25A0    SGemojifilledsquare\n\u25B1    SGemojiparallelogram\n\u25B0    SGemojifilledparallelogram\n\u25B1    SGemojiiamaparallelogram\n\u25CB    SGemojicircle\n\u25CF    SGemojifilledcircle\n\u25B3    SGemojitriangle\n\u25B2    SGemojifilledtriangle\n\u2B21    SGemojihexagon\n\u2B22    SGemojifilledhexagon\n\u2B20    SGemojipentagon\n\u2B1F    SGemojifilledpentagon\n\u0378    SGemojiflag\n\u0378    SGemojimark\n\u0378    SGemojiSingaporemark\n\u0378    SGemojiSGmark");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "fancy letters", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2102    SGmathbbC\n\u210D    SGmathbbH\n\u2115    SGmathbbN\n\u2119    SGmathbbP\n\u211A    SGmathbbQ\n\u211D    SGmathbbR\n\u2124    SGmathbbZ\n\u2145    SGmathbbD\n\u2146    SGmathbbd\n\u2147    SGmathbbe\n\u2148    SGmathbbi\n\u2149    SGmathbbj\n\u2102    SGbubbleC\n\u210D    SGbubbleH\n\u2115    SGbubbleN\n\u2119    SGbubbleP\n\u211A    SGbubbleQ\n\u211D    SGbubbleR\n\u2124    SGbubbleZ\n\u2145    SGbubbleD\n\u2146    SGbubbled\n\u2147    SGbubblee\n\u2148    SGbubblei\n\u2149    SGbubblej\n\u210A    SGscriptg\n\u210B    SGscriptH\n\u2110    SGscriptI\n\u2112    SGscriptL\n\u2113    SGscriptl\n\u2118    SGscriptP\n\u211B    SGscriptR\n\u212C    SGscriptB\n\u212F    SGscripte\n\u2130    SGscriptE\n\u2131    SGscriptF\n\u2133    SGscriptM\n\u2134    SGscripto\n\u210A    SGcursiveg\n\u210B    SGcursiveH\n\u2110    SGcursiveI\n\u2112    SGcursiveL\n\u2113    SGcursivel\n\u2118    SGcursiveP\n\u211B    SGcursiveR\n\u212C    SGcursiveB\n\u212F    SGcursivee\n\u2130    SGcursiveE\n\u2131    SGcursiveF\n\u2133    SGcursiveM\n\u2134    SGcursiveo\n\u210C    SGfrakturH\n\u2111    SGfrakturI\n\u211C    SGfrakturR\n\u2128    SGfrakturZ\n\u212D    SGfrakturC\n\u210C    SGfrakH\n\u2111    SGfrakI\n\u211C    SGfrakR\n\u2128    SGfrakZ\n\u212D    SGfrakC");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "control pictures", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2400    SGcpnul\n\u2401    SGcpsoh\n\u2402    SGcpstx\n\u2403    SGcpetx\n\u2404    SGcpeot\n\u2405    SGcpenq\n\u2406    SGcpack\n\u2407    SGcpbel\n\u2408    SGcpbs\n\u2409    SGcpht\n\u240A    SGcplf\n\u240B    SGcpvt\n\u240C    SGcpff\n\u240D    SGcpcr\n\u240E    SGcpso\n\u240F    SGcpsi\n\u2410    SGcpdle\n\u2411    SGcpdcone\n\u2412    SGcpdctwo\n\u2413    SGcpdcthree\n\u2414    SGcpdcfour\n\u2415    SGcpnak\n\u2416    SGcpsyn\n\u2417    SGcpetb\n\u2418    SGcpcan\n\u2419    SGcpem\n\u241A    SGcpsub\n\u241B    SGcpesc\n\u241C    SGcpfs\n\u241D    SGcpgs\n\u241E    SGcprs\n\u241F    SGcpus\n\u2420    SGcpsp\n\u2421    SGcpdel\n\u2424    SGcpnl");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "table borders", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2003    SGtablenone\n\u2575    SGtableup\n\u2577    SGtabledown\n\u2574    SGtableleft\n\u2576    SGtableright\n\u2502    SGtablevertical\n\u2500    SGtablehorizontal\n\u2571    SGtableleftdiagonal\n\u2572    SGtablerightdiagonal\n\u2573    SGtablecross\n\u2518    SGtableupleft\n\u2514    SGtableupright\n\u2510    SGtabledownleft\n\u250C    SGtabledownright\n\u252C    SGtableallexceptup\n\u2534    SGtableallexceptdown\n\u251C    SGtableallexceptleft\n\u2524    SGtableallexceptright\n\u253C    SGtableall");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "progress bar", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u2003    SGpbleftzero\n\u258F    SGpbleftone\n\u258E    SGpblefttwo\n\u258D    SGpbleftthree\n\u258C    SGpbleftfour\n\u258B    SGpbleftfive\n\u258A    SGpbleftsix\n\u2589    SGpbleftseven\n\u2588    SGpblefteight\n\u2003    SGpbbottomzero\n\u2581    SGpbbottomone\n\u2582    SGpbbottomtwo\n\u2583    SGpbbottomthree\n\u2584    SGpbbottomfour\n\u2585    SGpbbottomfive\n\u2586    SGpbbottomsix\n\u2587    SGpbbottomseven\n\u2588    SGpbbottomeight\n\u2590    SGpbrightfour\n\u2580    SGpbtopfour\n\u2595    SGphrightone\n\u2594    SGpbtopone\n\u2003    SGpbshadenone\n\u2591    SGpbshadelight\n\u2592    SGpbshademedium\n\u2593    SGpbshadedark\n\u2588    SGpbshadefull");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    new SGWTextLabel(x, "OAS (Optical Answer Sheet) bubbles", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Left, false);
    s = SGXString("\u24EA    SGoaszero\n\u2460    SGoasone\n\u2461    SGoastwo\n\u2462    SGoasthree\n\u2463    SGoasfour\n\u2464    SGoasfive\n\u2465    SGoassix\n\u2466    SGoasseven\n\u2467    SGoaseight\n\u2468    SGoasnine\n\u24B6    SGoasA\n\u24B7    SGoasB\n\u24B8    SGoasC\n\u24B9    SGoasD\n\u24BA    SGoasE\n\u24BB    SGoasF\n\u24BC    SGoasG\n\u24BD    SGoasH\n\u24BE    SGoasI\n\u24BF    SGoasJ\n\u24C0    SGoasK\n\u24C1    SGoasL\n\u24C2    SGoasM\n\u24C3    SGoasN\n\u24C4    SGoasO\n\u24C5    SGoasP\n\u24C6    SGoasQ\n\u24C7    SGoasR\n\u24C8    SGoasS\n\u24C9    SGoasT\n\u24CA    SGoasU\n\u24CB    SGoasV\n\u24CC    SGoasW\n\u24CD    SGoasX\n\u24CE    SGoasY\n\u24CF    SGoasZ\n\u24D0    SGoasa\n\u24D1    SGoasb\n\u24D2    SGoasc\n\u24D3    SGoasd\n\u24D4    SGoase\n\u24D5    SGoasf\n\u24D6    SGoasg\n\u24D7    SGoash\n\u24D8    SGoasi\n\u24D9    SGoasj\n\u24DA    SGoask\n\u24DB    SGoasl\n\u24DC    SGoasm\n\u24DD    SGoasn\n\u24DE    SGoaso\n\u24DF    SGoasp\n\u24E0    SGoasq\n\u24E1    SGoasr\n\u24E2    SGoass\n\u24E3    SGoast\n\u24E4    SGoasu\n\u24E5    SGoasv\n\u24E6    SGoasw\n\u24E7    SGoasx\n\u24E8    SGoasy\n\u24E9    SGoasz");
    new SGWLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    s = "    In addition to these fixed commands, you also have the special command \"unicode\" which allows you to enter any Unicode Basic Multilingual Plane character. For example, SG-\\unicode24B6 (may be different depending on your prefix) gives you the OAS bubble for A.";
    new SGWSequentialLongLabel(x, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(x, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    return bg;
}

void SGWSingCorrectCustomisationPage::showCommandList(){
    SGWBackground::enable(SGWSingCorrectCustomisationPage::commandListInstance, &SGWSingCorrectCustomisationPage::initialiseCommandList, nullptr);
}

void SGWSingCorrectCustomisationPage::exitCommandList(){
    SGWBackground::disable(SGWSingCorrectCustomisationPage::commandListInstance);
}
