#ifndef SGXCENTRAL_H
#define SGXCENTRAL_H

#include <QObject>
#include "../userDefinedClasses/sgusignalemitter.h"
#include "../widgets/sgxrootwidget.h"
#include "../primitives/sgxcolourrgba.h"

class SGXCentral : public QObject // non instantiable class for essential application data that should not be modified by the user
{
    Q_OBJECT // NOLINT
public:
    SGXCentral() = delete;
    SGXCentral(const SGXCentral&) = delete;
    SGXCentral(SGXCentral&&) = delete;
    SGXCentral& operator=(const SGXCentral&) = delete;
    SGXCentral& operator=(SGXCentral&&) = delete;
    ~SGXCentral() override = default;
    static void initialise(); // initialisation function run when app opens
    static void terminate(); // termination function run when app closes
    static QFont* standardFont; // font used for displaying text, recommended to use SingScript.sg, which is default font file
    static QFont* iconsFont; // font containing icons, SingScript.sg is placeholder, icons font should use Unicode private range to avoid confusion, picture icons are not supported by SGEXTN due to performance reasons
    static SGUSignalEmitter* signalEmitter; // signal emitter allowing UI resizing and refreshing
    static float applicationWindowWidth; // width of application window
    static float applicationWindowHeight; // height of application window
    static float renderAreaWidth; // width of area used to render UI
    static float renderAreaHeight; // height of area used to render UI
    static float sizeUnit; // unit used to measure UI size, 1 is minimum height of text
    static SGXRootWidget* rootWindow; // root window of application
    static SGXColourRGBA noColour; // transparent
};

#endif // SGXCENTRAL_H
