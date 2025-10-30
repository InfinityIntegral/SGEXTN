#include <private_api_Widgets/SGXSingCorrectQuickInterface.h>
#include <SGXSingCorrectCore.h>
#include <QString>
#include <SGXString.h>

QString SGXSingCorrectQuickInterface::correct(const QString &s) const { // NOLINT(readability-convert-member-functions-to-static)
    const SGXString s0 = "";
    (*s0.data) = s;
    return (*SGXSingCorrectCore::correct(s0).data);
}
