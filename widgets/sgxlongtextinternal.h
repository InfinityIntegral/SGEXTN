#ifndef SGXLONGTEXTINTERNAL_H
#define SGXLONGTEXTINTERNAL_H

#include <QWidget>
#include "../primitives/sgxcolourrgba.h"
#include <QColor>
#include <QString>
#include <QFont>

class SGXLongTextInternal : public QWidget // internal class for SGXLongText, similar to multiline SGXText with no fixed height
{
    Q_OBJECT // NOLINT
public:
    SGXLongTextInternal(QWidget* parent); // create text label
    QColor backgroundColour; // colour used to shade background
    QColor foregroundColour; // colour used to shade text
    QString s; // text displayed in label
    QFont font; // font used for label with size set
    void setText(const QString& s); // function to change text and update widget
    void setBackgroundColour(); // set background colour to default colour
    void setBackgroundColour(int themeColourIndex); // set background colour to theme colour
    void setBackgroundColour(SGXColourRGBA customColour); // set background colour to custom colour
    void setForegroundColour(); // set text colour to default colour
    void setForegroundColour(int themeColourIndex); // set text colour to theme colour
    void setForegroundColour(SGXColourRGBA customColour); // set text colour to custom colour
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
};

#endif // SGXLONGTEXTINTERNAL_H
