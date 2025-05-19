#ifndef SGGENERALLIBRARY_H
#define SGGENERALLIBRARY_H

#include <QObject>

class SGGeneralLibrary : public QObject
{
    Q_OBJECT
public:
    static QFont* SingScriptSG;
    static void SetUIStyle(QWidget* obj, QString& k, QString& v);
    static QString stylesheetfieldbackgroundcolour;
    static QString stylesheetfieldtextcolour;
    static QString stylesheetfieldfontsize;
    static QString stylesheetfieldborder;
    static QString stylesheetfieldselectedtextcolour;
    static QString stylesheetfieldselectedbackgroundcolour;
    static QString stylesheetfieldscrollbarwidth;
    static QString stylesheetnoborder;
    static void updatefontsize(QWidget* obj);
    static QString ColourUintToCSS(uint c);
    static uint ColourCSSToUint(QString& s);
    static void setscrollviewstylesheet(QWidget* obj);
    static void updatescrollbarwidth(QWidget* obj);
    static float plusinf;
    static float minusinf;
private:
    SGGeneralLibrary(){}
    ~SGGeneralLibrary(){}
};

#endif // SGGENERALLIBRARY_H
