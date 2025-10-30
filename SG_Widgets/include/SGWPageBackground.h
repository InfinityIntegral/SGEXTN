#ifndef SGWPAGEBACKGROUND_H
#define SGWPAGEBACKGROUND_H

#include <SGWBackground.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWWidget;
class SG_WIDGETS_DLL SGWPageBackground : public SGWBackground
{
public:
    SGWPageBackground(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour);
};

#endif // SGWPAGEBACKGROUND_H
