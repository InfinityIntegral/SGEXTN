#ifndef SGWDEFAULTFONTS_H
#define SGWDEFAULTFONTS_H

#include <SGXString.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGWDefaultFonts
{
public:
    SGWDefaultFonts() = delete;
    static SGXString textFont;
    static SGXString iconsFont;
    static void addFont(const SGXString& fileName);
};

#endif // SGWDEFAULTFONTS_H
