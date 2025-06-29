#ifndef SGXFILEWRITER_H
#define SGXFILEWRITER_H

#include <QObject>
#include <QFile>
#include <qtmetamacros.h>

class SGXFileWriter : public QObject
{
    Q_OBJECT
public:
    SGXFileWriter(const QString& s);
    SGXFileWriter(const SGXFileWriter&) = delete;
    SGXFileWriter(const SGXFileWriter&&) = delete;
    SGXFileWriter& operator=(const SGXFileWriter&) = delete;
    SGXFileWriter& operator=(const SGXFileWriter&&) = delete;
    ~SGXFileWriter() override;
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

#endif // SGXFILEWRITER_H
