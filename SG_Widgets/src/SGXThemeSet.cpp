#include <private_api_Widgets/SGXThemeSet.h>
#include <SGXString.h>
#include <SGLArray.h>
#include <SGXColourRGBA.h>
#include <SGXThemeColours.h>

SGXThemeSet::SGXThemeSet(const SGXString &themeName, const SGLArray<SGXColourRGBA> &colours){
    (*this).themeName = themeName;
    (*this).colours = colours;
}

SGXString SGXThemeSet::styleText = "You are using SGEXTN Sincerity UI, a PSLE inspired UI style for all SGEXTN applications\nYou can use various UI elements on this PSLE themed page to see what the theme that you selected would look like.\n\nHelen and Ivan had the same amount of coins. Helen had a number of 50-cent coins, and 64 20-cent coins. These coins had a mass of 1.134kg. Ivan had a number of 50-cent coins and 104 20-cent coins.\n1) Who has more money in coins and by how much?\n2) Given that each 50-cent coin is 2.7g more heavier than a 20-cent coin, what is the mass of Ivan's coins in kilograms?";
// also there is "do not write in this space" on the right, "previous" and "next" buttons, and 2 "ans:" input fields at the bottom

SGXThemeSet SGXThemeSet::standardLight = SGXThemeSet("Sincerity UI (light)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(255, 0, 200), false));
SGXThemeSet SGXThemeSet::standardDark = SGXThemeSet("Sincerity UI (dark)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(255, 0, 200), true));
SGXThemeSet SGXThemeSet::englishLight = SGXThemeSet("English Language (light)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(0, 121, 185), false));
SGXThemeSet SGXThemeSet::englishDark = SGXThemeSet("English Language (dark)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(0, 121, 185), true));
SGXThemeSet SGXThemeSet::mathLight = SGXThemeSet("Mathematics (light)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(240, 99, 13), false));
SGXThemeSet SGXThemeSet::mathDark = SGXThemeSet("Mathematics (dark)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(240, 99, 13), true));
SGXThemeSet SGXThemeSet::scienceLight = SGXThemeSet("Science (light)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(0, 156, 67), false));
SGXThemeSet SGXThemeSet::scienceDark = SGXThemeSet("Science (dark)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(0, 156, 67), true));
SGXThemeSet SGXThemeSet::chineseLight = SGXThemeSet("华文 (light)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(236, 70, 112), false));
SGXThemeSet SGXThemeSet::chineseDark = SGXThemeSet("华文 (dark)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(236, 70, 112), true));
SGXThemeSet SGXThemeSet::malayLight = SGXThemeSet("Bahasa Melayu (light)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(161, 80, 34), false));
SGXThemeSet SGXThemeSet::malayDark = SGXThemeSet("Bahasa Melayu (dark)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(161, 80, 34), true));
SGXThemeSet SGXThemeSet::tamilLight = SGXThemeSet("தமிழ் (light)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(113, 82, 149), false));
SGXThemeSet SGXThemeSet::tamilDark = SGXThemeSet("தமிழ் (dark)", SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(113, 82, 149), true));
