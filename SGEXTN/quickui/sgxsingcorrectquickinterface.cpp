#include "sgxsingcorrectquickinterface.h"
#include "../SingCorrect/sgxsingcorrectcore.h"
#include <QString>

QString SGXSingCorrectQuickInterface::correct(const QString &s) const { // NOLINT(readability-convert-member-functions-to-static)
    return SGXSingCorrectCore::correct(s);
}
