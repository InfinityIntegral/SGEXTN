#include "sgwdefaultfonts.h"
#include "../../primitives/sgxstring.h"
#include <QFontDatabase>

SGXString SGWDefaultFonts::textFont = "SingScript.sg";
SGXString SGWDefaultFonts::iconsFont = "AppIcons.sg";

void SGWDefaultFonts::addFont(const SGXString &fileName){
    QFontDatabase::addApplicationFont(*fileName.data);
}
