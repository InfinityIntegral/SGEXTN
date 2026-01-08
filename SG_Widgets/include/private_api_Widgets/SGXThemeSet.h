#ifndef SGXTHEMESET_H
#define SGXTHEMESET_H

#include <private_api_Widgets/SG_Build_Widgets.h>

#include <SGXString.h>
#include <SGLArray.h>
#include <SGXColourRGBA.h>

class SG_WIDGETS_DLL SGXThemeSet {
public:
    SGXThemeSet(const SGXString& themeName, const SGLArray<SGXColourRGBA>& colours);
    SGXString themeName;
    SGLArray<SGXColourRGBA> colours;
    static SGXString styleText;
    static SGXThemeSet standardLight;
    static SGXThemeSet standardDark;
    static SGXThemeSet mathLight;
    static SGXThemeSet mathDark;
    static SGXThemeSet scienceLight;
    static SGXThemeSet scienceDark;
    static SGXThemeSet englishLight;
    static SGXThemeSet englishDark;
    static SGXThemeSet chineseLight;
    static SGXThemeSet chineseDark;
    static SGXThemeSet malayLight;
    static SGXThemeSet malayDark;
    static SGXThemeSet tamilLight;
    static SGXThemeSet tamilDark;
};

#endif // SGXTHEMESET_H
