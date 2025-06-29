#ifndef SGXFILEREADER_H
#define SGXFILEREADER_H

#include <QObject>
#include <QFile>
#include <qtmetamacros.h>

class SGXFileReader : public QObject
{
    Q_OBJECT
public:
    SGXFileReader(const QString& s);
    SGXFileReader(const SGXFileReader&) = delete;
    SGXFileReader(const SGXFileReader &&) = delete;
    SGXFileReader& operator=(const SGXFileReader&) = delete;
    SGXFileReader& operator=(const SGXFileReader&&) = delete;
    ~SGXFileReader() override;
    QFile* fileControl;
    QDataStream* fileData;
/*
bool
char
int
unsigned int
long long
unsigned long long
float
double
QString

SGXColourRGBA
SGXColourHSLA
SGXIdentifier
SGXTimeStamp
SGXVector2

get location
set location
*/
};

#endif // SGXFILEREADER_H
