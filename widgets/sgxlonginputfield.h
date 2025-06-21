#ifndef SGXLONGINPUTFIELD_H
#define SGXLONGINPUTFIELD_H

#include <QScrollArea>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QWidget>
#include <QString>
#include <QColor>
#include <QFont>
#include "../primitives/sgxcolourrgba.h"
#include <QList>

class SGXLongInputFieldInternal;
class SGXLongInputField : public QScrollArea // scrollable multiline input field
{
    Q_OBJECT // NOLINT
public:
    SGXLongInputField(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float s1, float s0, float f1, float f0); // create long input field
    // the value of each size and location variable is linear factor * width or height of rendering space + constant factor * size unit
    // ensure that x0 + w0 < 13.5 * (1 - x1 - w1) and y0 + h0 < 13.5 * (1 - y1 - h1) to avoid widgets going off screen
    // you are recommended to keep 0.5 * size unit of margin on the 4 sides of the screen
    float x1; // linear factor of x position
    float x0; // constant factor of x position
    float y1; // linear factor of y position
    float y0; // constant factor of y position
    float w1; // linear factor of width
    float w0; // constant factor of width
    float h1; // linear factor of height
    float h0; // constant factor of height
    float s1; // linear factor of scroll bar width
    float s0; // constant factor of scroll bar height
    float f1; // linear factor of font size
    float f0; // constant factor of font size
    bool hovering; // indicates if input field is hovered over
    bool focused; // indicates if input field is focused
    bool invalid; // indicates if text is invalid
    QColor backgroundColour; // colour used to shade background
    QColor foregroundColour; // colour used to shade text
    QColor selectionHighlightsBackgroundColour; // colour used to shade background of selected text
    QColor selectionHighlightsForegroundColour; // colour used to shade selected text
    QColor hoverBackgroundColour; // colour used to shade background when hovered over
    QColor hoverForegroundColour; // colour used to shade text when hovered over
    QColor focusedBackgroundColour; // colour used to shade background when focused
    QColor focusedForegroundColour; // colour used to shade text when focused
    QColor invalidBackgroundColour; // colour used to shade background when text is invalid
    QColor invalidForegroundColour; // colour used to shade text when text is invalid
    QFont font; // font used for label with size set
    void setBackgroundColour(); // set background colour to default colour
    void setBackgroundColour(int themeColourIndex); // set background colour to theme colour
    void setBackgroundColour(SGXColourRGBA customColour); // set background colour to custom colour
    void setForegroundColour(); // set text colour to default colour
    void setForegroundColour(int themeColourIndex); // set text colour to theme colour
    void setForegroundColour(SGXColourRGBA customColour); // set text colour to custom colour
    void setSelectionHighlightsBackgroundColour(); // set selection highlight background colour to default colour
    void setSelectionHighlightsBackgroundColour(int themeColourIndex); // set selection highlight colour to theme colour
    void setSelectionHighlightsBackgroundColour(SGXColourRGBA customColour); // set selection highlight colour to custom colour
    void setSelectionHighlightsForegroundColour(); // set selected text colour to default colour
    void setSelectionHighlightsForegroundColour(int themeColourIndex); // set selected text colour to theme colour
    void setSelectionHighlightsForegroundColour(SGXColourRGBA customColour); // set selected text colour to custom colour;
    void setHoverBackgroundColour(); // set background colour when hovering to default colour
    void setHoverBackgroundColour(int themeColourIndex); // set background colour when hovering to theme colour
    void setHoverBackgroundColour(SGXColourRGBA customColour); // set background colour when hovering to custom colour
    void setHoverForegroundColour(); // set text colour when hovering to default colour
    void setHoverForegroundColour(int themeColourIndex); // set text colour when hovering to theme colour
    void setHoverForegroundColour(SGXColourRGBA customColour); // set text colour when hovering to custom colour
    void setFocusedBackgroundColour(); // set background colour when focused to default colour
    void setFocusedBackgroundColour(int themeColourIndex); // set background colour when focused to theme colour
    void setFocusedBackgroundColour(SGXColourRGBA customColour); // set background colour when focused to custom colour
    void setFocusedForegroundColour(); // set text colour when focused to default colour
    void setFocusedForegroundColour(int themeColourIndex); // set text colour when focused to theme colour
    void setFocusedForegroundColour(SGXColourRGBA customColour); // set text colour when focused to custom colour
    void setInvalidBackgroundColour(); // set background colour when text is invalid to default colour
    void setInvalidBackgroundColour(int themeColourIndex); // set background colour when text is invalid to theme colour
    void setInvalidBackgroundColour(SGXColourRGBA customColour); // set background colour when text is invalid to custom colour
    void setInvalidForegroundColour(); // set text colour when text is invalid to default colour
    void setInvalidForegroundColour(int themeColourIndex); // set text colour when text is invalid to theme colour
    void setInvalidForegroundColour(SGXColourRGBA customColour); // set text colour when text is invalid to custom colour
    void setInvalid(const QString& s); // set input field to invalid state to warn about invalid text input
    int cursorPosition; // contain position of cursor
    int selectionRangeEnd; // contain other end of selected text (not the side with cursor)
    void setInput(const QString& s); // set contents of input field
    [[nodiscard]] QString getInput() const; // get contents of input field
    SGXLongInputFieldInternal* displayInternal; // list of ints, each pair indicating a line
    QList<int> lineGaps; // list of ints, each pair indicating a line
    void splitLine(); // split string into lines for rendering
public slots: // NOLINT
    void resizeObject(); // automatic resizing of input field
    void unsetInvalid(); // remove invalid status after warning of 1 second
};

#endif // SGXLONGINPUTFIELD_H
