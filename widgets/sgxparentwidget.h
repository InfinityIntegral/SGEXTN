#ifndef SGXPARENTWIDGET_H
#define SGXPARENTWIDGET_H

#include <QWidget>

class SGXParentWidget : public QWidget // render space widget, not called SGXRenderSpaceWidget to avoid confusion with OpenGL rendering
{
    Q_OBJECT // NOLINT
public:
    SGXParentWidget(); // create render space widget
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
public slots: // NOLINT
    void resizeObject(); // resize to center render space
};

#endif // SGXPARENTWIDGET_H
