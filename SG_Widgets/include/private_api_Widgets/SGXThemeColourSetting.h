#ifndef SGXTHEMECOLOURSETTING_H
#define SGXTHEMECOLOURSETTING_H

#include <QObject>
#include <QColor>
#include <SGXColourRGBA.h>
#include <qtmetamacros.h>
#include <SGLArray.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGXThemeColourSetting : public QObject
{
    Q_OBJECT
public:
    SGXThemeColourSetting() = default;
    [[nodiscard]] Q_INVOKABLE QColor getThemeColour(int x) const;
};

#endif // SGXTHEMECOLOURSETTING_H
