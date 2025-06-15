#ifndef SGXCENTRAL_H
#define SGXCENTRAL_H

#include <QObject>
#include <memory>

class SGXCentral : public QObject
{
    Q_OBJECT // NOLINT
public:
    SGXCentral() = delete;
    SGXCentral(const SGXCentral&) = delete;
    SGXCentral(SGXCentral&&) = delete;
    SGXCentral& operator=(const SGXCentral&) = delete;
    SGXCentral& operator=(SGXCentral&&) = delete;
    ~SGXCentral() override = default;
    static void initialise();
    static void terminate();
    static std::unique_ptr<QFont> standardFont;
    static std::unique_ptr<QFont> iconsFont;
};

#endif // SGXCENTRAL_H
