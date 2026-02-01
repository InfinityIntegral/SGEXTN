#pragma once
#include <SGEXTN_ApplicationBase_String.h>

namespace SGEXTN {
namespace Containers { template <typename T, typename Comparator> class PriorityQueue; }
namespace Containers { template <typename T> class Vector; }
namespace ApplicationBase {
class RegistryEntry;
class RegistryEntryComparator;
class BUILDLAH_DLL_SGEXTN_ApplicationBase InitSetup {
public:
    static SGEXTN::ApplicationBase::String applicationName;
    static SGEXTN::ApplicationBase::String applicationVersion;
    static SGEXTN::ApplicationBase::String organisationName;
    static SGEXTN::ApplicationBase::String organisationDomain;
    static SGEXTN::ApplicationBase::String folderName;
    static SGEXTN::ApplicationBase::String applicationDisplayName;
    static SGEXTN::ApplicationBase::String pathToAppIcon;
    static bool isConsoleApp;
    static void addInfoWebsite(const SGEXTN::ApplicationBase::String& link);
    static int (*userMain)(int, char**);
    static SGEXTN::Containers::PriorityQueue<SGEXTN::ApplicationBase::RegistryEntry, SGEXTN::ApplicationBase::RegistryEntryComparator>* private_initialiseFunctionQueue;
    static SGEXTN::Containers::PriorityQueue<SGEXTN::ApplicationBase::RegistryEntry, SGEXTN::ApplicationBase::RegistryEntryComparator>* private_terminationFunctionQueue;
    static void private_initialise();
    static void private_terminate();
    static SGEXTN::Containers::Vector<SGEXTN::ApplicationBase::String>* private_infoWebsites;
    static int private_argc;
    static char** private_argv;
    static int private_priorityGap;
    static void private_setLocale();
    static void private_setCoreAppMetadata();
    static void private_createConsoleApp();
    static void private_runUserMain();
    static int private_returnValue;
    static bool private_runFinished;
    static SGEXTN::ApplicationBase::RegistryEntry private_setLocaleInit;
    static SGEXTN::ApplicationBase::RegistryEntry private_setCoreAppMetadataInit;
    static SGEXTN::ApplicationBase::RegistryEntry private_createConsoleAppInit;
    static SGEXTN::ApplicationBase::RegistryEntry private_runUserMainInit;
};
}
}

/*
before everything else - copy argc argv, call init
8 - set locale
7 - init log file | by SGEXTN::NambagaFS
6 - allow user inject metadata and indicate if it is a console app | by user
5 - set QCoreApplication metadata
4 - allow user to parse cmd3 args | by user
3 - reserved for SGEXTN to parse cmd args
2 - create QCoreApplication if console app
1 - init file system | by SGEXTN::NambagaFS
0 - exit if console app, only GUI apps will do the remaining steps | everything below by SGEXTN::SayangA and higher layers
-1 - set Qt Quick style
-2 - create QGuiApplication and bind aboutToQuit signal to appropriate slot
-3 - set window icon and display name
-4 - create QQmlApplicationEngine
-5 - allow user to set custom theme
-6 - load theme colours preferences
-7 - load font size preferences
-8 - load fonts
-9 - allow user to set default font
-10 - init QML side singleton for resizing of GUI
-11 - load QML blank root window that does nothing
-12 - connect QML side singleton for resizing with C++ side logic
-13 - create QML template components
-14 - actually load QML
-15 - refresh screen to update window size
-16 - init SingCorrect module (for unicode input)
-17 - load SingCorrect preferences
-18 - user application init function
*/
