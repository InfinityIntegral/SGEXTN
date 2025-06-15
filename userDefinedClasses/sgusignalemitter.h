#ifndef SGUSIGNALEMITTER_H
#define SGUSIGNALEMITTER_H

#include <QObject>

class SGUSignalEmitter : public QObject // singleton pattern class used to control UI resizing and updating, user should not instantiate this class
{
    Q_OBJECT // NOLINT
public:
    void sendSignals(); // function run when window is resized, allowing widgets contained to resize automatically
signals: // NOLINT
    void updateScreen(); // signal that resize slots on widgets can bind to, this one specifically is for the SGEXTN default widgets, but you can add more signals below for different parts of your app
    // void yourSignal();
};

#endif // SGUSIGNALEMITTER_H
