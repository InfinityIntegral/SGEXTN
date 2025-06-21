#ifndef SGXLONGINPUTFIELDINTERNAL_H
#define SGXLONGINPUTFIELDINTERNAL_H

#include <QTextEdit>
#include <QEnterEvent>
#include <QEvent>
#include <QFocusEvent>
#include <QMouseEvent>
#include <QPaintEvent>

class SGXLongInputField;
class SGXLongInputFieldInternal : public QTextEdit // internal class for SGXLongInputField, similar to SGXInputField but multiline
{
    Q_OBJECT // NOLINT
public:
    SGXLongInputFieldInternal(SGXLongInputField* parent); // create input field
    SGXLongInputField* ref; // pointer to widget with all the information
    void enterEvent(QEnterEvent*) override; // NOLINT(readability-named-parameter)
    void leaveEvent(QEvent*) override; // NOLINT(readability-named-parameter)
    void focusInEvent(QFocusEvent* event) override; // update input field appearance when focused
    void focusOutEvent(QFocusEvent* event) override; // update input field appearance when unfocused
    void mousePressEvent(QMouseEvent* event) override; // update cursor position when input field is pressed
    void mouseMoveEvent(QMouseEvent* event) override; // update selection range when mouse is moved while being pressed
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
public slots: // NOLINT
    void refreshText(); // refresh display when text has been updated
};

#endif // SGXLONGINPUTFIELDINTERNAL_H
