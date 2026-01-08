#include <private_api_Widgets/SGXThemeSet.h>
#include <SGXString.h>
#include <SGLArray.h>
#include <SGXColourRGBA.h>

SGXThemeSet::SGXThemeSet(const SGXString &themeName, const SGLArray<SGXColourRGBA> &colours){
    (*this).themeName = themeName;
    (*this).colours = colours;
}

SGXString SGXThemeSet::styleText = "You are using SGEXTN Sincerity UI, a PSLE inspired UI style for all SGEXTN applications\nYou can use various UI elements on this PSLE themed page to see what the theme that you selected would look like.\n\nHelen and Ivan had the same amount of coins. Helen had a number of 50-cent coins, and 64 20-cent coins. These coins had a mass of 1.134kg. Ivan had a number of 50-cent coins and 104 20-cent coins.\n1) Who has more money in coins and by how much?\n2) Given that each 50-cent coin is 2.7g more heavier than a 20-cent coin, what is the mass of Ivan's coins in kilograms?";
// also there is "do not write in this space" on the right, "previous" and "next" buttons, and 2 "ans:" input fields at the bottom

SGXThemeSet SGXThemeSet::standardLight = SGXThemeSet("Sincerity UI (light)", SGLArray<SGXColourRGBA>(SGXColourRGBA(202, 0, 159), SGXColourRGBA(168, 0, 132), SGXColourRGBA(123, 0, 96), SGXColourRGBA(255, 243, 250), SGXColourRGBA(255, 217, 240), SGXColourRGBA(255, 186, 229)));
SGXThemeSet SGXThemeSet::standardDark = SGXThemeSet("Sincerity UI (dark)", SGLArray<SGXColourRGBA>(SGXColourRGBA(255, 186, 229), SGXColourRGBA(255, 217, 240), SGXColourRGBA(255, 243, 250), SGXColourRGBA(123, 0, 96), SGXColourRGBA(168, 0, 132), SGXColourRGBA(202, 0, 159)));
SGXThemeSet SGXThemeSet::englishLight = SGXThemeSet("English Language (light)", SGLArray<SGXColourRGBA>(SGXColourRGBA(0, 132, 202), SGXColourRGBA(0, 110, 168), SGXColourRGBA(0, 80, 123), SGXColourRGBA(243, 248, 255), SGXColourRGBA(217, 233, 255), SGXColourRGBA(186, 216, 255)));
SGXThemeSet SGXThemeSet::englishDark = SGXThemeSet("English Language (dark)", SGLArray<SGXColourRGBA>(SGXColourRGBA(186, 216, 255), SGXColourRGBA(217, 233, 255), SGXColourRGBA(243, 248, 255), SGXColourRGBA(0, 80, 123), SGXColourRGBA(0, 110, 168), SGXColourRGBA(0, 132, 202)));
SGXThemeSet SGXThemeSet::mathLight = SGXThemeSet("Mathematics (light)", SGLArray<SGXColourRGBA>(SGXColourRGBA(202, 83, 11), SGXColourRGBA(168, 69, 9), SGXColourRGBA(123, 51, 7), SGXColourRGBA(255, 245, 243), SGXColourRGBA(255, 223, 217), SGXColourRGBA(255, 198, 186)));
SGXThemeSet SGXThemeSet::mathDark = SGXThemeSet("Mathematics (dark)", SGLArray<SGXColourRGBA>(SGXColourRGBA(255, 198, 186), SGXColourRGBA(255, 223, 217), SGXColourRGBA(255, 245, 243), SGXColourRGBA(123, 51, 7), SGXColourRGBA(168, 69, 9), SGXColourRGBA(202, 83, 11)));
SGXThemeSet SGXThemeSet::scienceLight = SGXThemeSet("Science (light)", SGLArray<SGXColourRGBA>(SGXColourRGBA(0, 202, 87), SGXColourRGBA(0, 168, 72), SGXColourRGBA(0, 123, 53), SGXColourRGBA(243, 255, 245), SGXColourRGBA(217, 255, 223), SGXColourRGBA(186, 255, 199)));
SGXThemeSet SGXThemeSet::scienceDark = SGXThemeSet("Science (dark)", SGLArray<SGXColourRGBA>(SGXColourRGBA(186, 255, 199), SGXColourRGBA(217, 255, 223), SGXColourRGBA(243, 255, 245), SGXColourRGBA(0, 123, 53), SGXColourRGBA(0, 168, 72), SGXColourRGBA(0, 202, 87)));
SGXThemeSet SGXThemeSet::chineseLight = SGXThemeSet("华文 (light)", SGLArray<SGXColourRGBA>(SGXColourRGBA(196, 58, 93), SGXColourRGBA(163, 48, 77), SGXColourRGBA(119, 35, 56), SGXColourRGBA(254, 244, 245), SGXColourRGBA(253, 220, 224), SGXColourRGBA(251, 191, 201)));
SGXThemeSet SGXThemeSet::chineseDark = SGXThemeSet("华文 (dark)", SGLArray<SGXColourRGBA>(SGXColourRGBA(251, 191, 201), SGXColourRGBA(253, 220, 224), SGXColourRGBA(254, 244, 245), SGXColourRGBA(119, 35, 56), SGXColourRGBA(163, 48, 77), SGXColourRGBA(196, 58, 93)));
SGXThemeSet SGXThemeSet::malayLight = SGXThemeSet("Bahasa Melayu (light)", SGLArray<SGXColourRGBA>(SGXColourRGBA(199, 99, 42), SGXColourRGBA(166, 82, 35), SGXColourRGBA(121, 60, 26), SGXColourRGBA(255, 246, 243), SGXColourRGBA(254, 225, 218), SGXColourRGBA(253, 203, 189)));
SGXThemeSet SGXThemeSet::malayDark = SGXThemeSet("Bahasa Melayu (dark)", SGLArray<SGXColourRGBA>(SGXColourRGBA(253, 203, 189), SGXColourRGBA(254, 225, 218), SGXColourRGBA(255, 246, 243), SGXColourRGBA(121, 60, 26), SGXColourRGBA(166, 82, 35), SGXColourRGBA(199, 99, 42)));
SGXThemeSet SGXThemeSet::tamilLight = SGXThemeSet("தமிழ் (light)", SGLArray<SGXColourRGBA>(SGXColourRGBA(138, 100, 181), SGXColourRGBA(114, 83, 151), SGXColourRGBA(84, 61, 110), SGXColourRGBA(248, 246, 253), SGXColourRGBA(234, 226, 248), SGXColourRGBA(219, 203, 242)));
SGXThemeSet SGXThemeSet::tamilDark = SGXThemeSet("தமிழ் (dark)", SGLArray<SGXColourRGBA>(SGXColourRGBA(219, 203, 242), SGXColourRGBA(234, 226, 248), SGXColourRGBA(248, 246, 253), SGXColourRGBA(84, 61, 110), SGXColourRGBA(114, 83, 151), SGXColourRGBA(138, 100, 181)));
