#ifndef SGWTEXTLABEL_H
#define SGWTEXTLABEL_H

#include <SGWLabel.h>
#include <SGWHorizontalAlignment.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGXString;
class SGWWidget;
class SG_WIDGETS_DLL SGWTextLabel : public SGWLabel
{
public:
    SGWTextLabel(SGWWidget* parent, const SGXString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGWHorizontalAlignment::Flag alignment, bool isWarning);
};

#endif // SGWTEXTLABEL_H
