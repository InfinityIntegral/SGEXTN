#include <SGWDefaultFonts.h>
#include <SGXString.h>
#include <QFontDatabase>

SGXString SGWDefaultFonts::textFont = "SingScript.sg";
SGXString SGWDefaultFonts::iconsFont = "AppIcons.sg";

void SGWDefaultFonts::addFont(const SGXString &fileName){
    QFontDatabase::addApplicationFont(*fileName.data);
}
