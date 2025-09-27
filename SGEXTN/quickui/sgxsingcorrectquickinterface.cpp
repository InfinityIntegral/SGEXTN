#include "sgxsingcorrectquickinterface.h"
#include "../SingCorrect/sgxsingcorrectcore.h"
#include <QString>
#include "../primitives/sgxstring.h"

QString SGXSingCorrectQuickInterface::correct(const QString &s) const { // NOLINT(readability-convert-member-functions-to-static)
    const SGXString s0 = "";
    (*s0.data) = s;
    return (*SGXSingCorrectCore::correct(s0).data);
}
