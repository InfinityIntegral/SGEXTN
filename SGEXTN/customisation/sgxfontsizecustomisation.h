#ifndef SGXFONTSIZECUSTOMISATION_H
#define SGXFONTSIZECUSTOMISATION_H

class SGXFontSizeCustomisation
{
public:
    SGXFontSizeCustomisation() = delete;
    static void loadFontSize();
    static void syncFontSize();
    static void updateFontSize();
    static float fontSize;
    static float defaultFontSize;
};

#endif // SGXFONTSIZECUSTOMISATION_H
