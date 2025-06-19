#ifndef SGXLAYOUT_H
#define SGXLAYOUT_H

#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"

class SGXLayout : public QWidget // layout used for managing components in complex UI systems, especially linear ones
{
    Q_OBJECT // NOLINT
public:
    SGXLayout(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)()); // create layout
    void paintEvent(QPaintEvent *) override; // NOLINT(readability-named-parameter)
public slots: // NOLINT
    void receiveUpdateCall() const; // schedule resize call, the resize call must be delayed so that it runs after resize functions on components managed by the layout
    void resizeObject(); // allow implementation of custom logic to manage UI
    virtual void resizeComponents(float w, float& h) = 0; // custom logic to manage UI appears here, provided is the width initialised to width of parent in size units and height set to zero, the implementation must set h to the height of the widget in size units for resizing
};

#endif // SGXLAYOUT_H
