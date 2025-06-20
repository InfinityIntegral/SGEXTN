#ifndef SGXLONGTEXTINTERNAL_H
#define SGXLONGTEXTINTERNAL_H

#include <QWidget>

class SGXLongText;
class SGXLongTextInternal : public QWidget // internal class for SGXLongText, similar to multiline SGXText with no fixed height
{
    Q_OBJECT // NOLINT
public:
    SGXLongTextInternal(SGXLongText* parent); // create text label
    SGXLongText* ref; // pointer to widget with all the information
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
};

#endif // SGXLONGTEXTINTERNAL_H
