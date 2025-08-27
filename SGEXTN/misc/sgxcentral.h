#ifndef SGXCENTRAL_H
#define SGXCENTRAL_H

class SGXCentral
{
public:
    SGXCentral() = delete;
    static void initialise();
    static void terminate();
};

#endif // SGXCENTRAL_H
