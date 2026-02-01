#include <SGEXTN_ApplicationBase_InitSetup.h>
#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_Containers_Vector.h>
#include <SGEXTN_Containers_PriorityQueue.h>
#include <SGEXTN_ApplicationBase_RegistryEntry.h>
#include <QLocale>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <QCoreApplication>

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::InitSetup::applicationName = "";
SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::InitSetup::applicationVersion = "";
SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::InitSetup::organisationName = "";
SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::InitSetup::organisationDomain = "";
SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::InitSetup::folderName = "";
SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::InitSetup::applicationDisplayName = "";
SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::InitSetup::pathToAppIcon = "";
bool SGEXTN::ApplicationBase::InitSetup::isConsoleApp = false;
int (*SGEXTN::ApplicationBase::InitSetup::userMain)(int, char**) = nullptr;
constinit SGEXTN::Containers::PriorityQueue<SGEXTN::ApplicationBase::RegistryEntry, SGEXTN::ApplicationBase::RegistryEntryComparator>* SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue = nullptr;
constinit SGEXTN::Containers::PriorityQueue<SGEXTN::ApplicationBase::RegistryEntry, SGEXTN::ApplicationBase::RegistryEntryComparator>* SGEXTN::ApplicationBase::InitSetup::private_terminationFunctionQueue = nullptr;
SGEXTN::Containers::Vector<SGEXTN::ApplicationBase::String>* SGEXTN::ApplicationBase::InitSetup::private_infoWebsites = nullptr;
int SGEXTN::ApplicationBase::InitSetup::private_argc = 0;
char** SGEXTN::ApplicationBase::InitSetup::private_argv = nullptr;
int SGEXTN::ApplicationBase::InitSetup::private_priorityGap = 1000000;
int SGEXTN::ApplicationBase::InitSetup::private_returnValue = 0;
bool SGEXTN::ApplicationBase::InitSetup::private_runFinished = false;

SGEXTN::ApplicationBase::RegistryEntry SGEXTN::ApplicationBase::InitSetup::private_setLocaleInit = SGEXTN::ApplicationBase::RegistryEntry(SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue, 8 * SGEXTN::ApplicationBase::InitSetup::private_priorityGap, &SGEXTN::ApplicationBase::InitSetup::private_setLocale);
SGEXTN::ApplicationBase::RegistryEntry SGEXTN::ApplicationBase::InitSetup::private_setCoreAppMetadataInit = SGEXTN::ApplicationBase::RegistryEntry(SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue, 5 * SGEXTN::ApplicationBase::InitSetup::private_priorityGap, &SGEXTN::ApplicationBase::InitSetup::private_setCoreAppMetadata);
SGEXTN::ApplicationBase::RegistryEntry SGEXTN::ApplicationBase::InitSetup::private_createConsoleAppInit = SGEXTN::ApplicationBase::RegistryEntry(SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue, 2 * SGEXTN::ApplicationBase::InitSetup::private_priorityGap, &SGEXTN::ApplicationBase::InitSetup::private_createConsoleApp);
SGEXTN::ApplicationBase::RegistryEntry SGEXTN::ApplicationBase::InitSetup::private_runUserMainInit = SGEXTN::ApplicationBase::RegistryEntry(SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue, 0, &SGEXTN::ApplicationBase::InitSetup::private_runUserMain);

void SGEXTN::ApplicationBase::InitSetup::addInfoWebsite(const SGEXTN::ApplicationBase::String& link){
    if(SGEXTN::ApplicationBase::InitSetup::private_infoWebsites == nullptr){
        SGEXTN::ApplicationBase::InitSetup::private_infoWebsites = new SGEXTN::Containers::Vector<SGEXTN::ApplicationBase::String>();
    }
    (*SGEXTN::ApplicationBase::InitSetup::private_infoWebsites).pushBack(link);
}

void SGEXTN::ApplicationBase::InitSetup::private_initialise(){
    while((*SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue).length() > 0){
        ((*SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue).top().private_attachedFunction)();
        (*SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue).pop();
        if(SGEXTN::ApplicationBase::InitSetup::private_runFinished == true){return;}
    }
    delete SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue;
    SGEXTN::ApplicationBase::InitSetup::private_initialiseFunctionQueue = nullptr;
}

void SGEXTN::ApplicationBase::InitSetup::private_terminate(){
    while((*SGEXTN::ApplicationBase::InitSetup::private_terminationFunctionQueue).length() > 0){
        ((*SGEXTN::ApplicationBase::InitSetup::private_terminationFunctionQueue).top().private_attachedFunction)();
        (*SGEXTN::ApplicationBase::InitSetup::private_terminationFunctionQueue).pop();
    }
    delete SGEXTN::ApplicationBase::InitSetup::private_terminationFunctionQueue;
    SGEXTN::ApplicationBase::InitSetup::private_terminationFunctionQueue = nullptr;
}

void SGEXTN::ApplicationBase::InitSetup::private_setLocale(){
    QLocale::setDefault(QLocale(QLocale::English, QLocale::Singapore));
}

void SGEXTN::ApplicationBase::InitSetup::private_setCoreAppMetadata(){
    if(SGEXTN::ApplicationBase::InitSetup::applicationName == ""){SGEXTN::Containers::Crash::crash("application crashed during initialisation as SGEXTN::ApplicationBase::InitSetup::applicationName is not set, pls set it during initialisation in a function with priority preferably at 6000000");}
    if(SGEXTN::ApplicationBase::InitSetup::applicationVersion == ""){SGEXTN::Containers::Crash::crash("application crashed during initialisation as SGEXTN::ApplicationBase::InitSetup::applicationVersion is not set, pls set it during initialisation in a function with priority preferably at 6000000");}
    if(SGEXTN::ApplicationBase::InitSetup::organisationName == ""){SGEXTN::Containers::Crash::crash("application crashed during initialisation as SGEXTN::ApplicationBase::InitSetup::organisationName is not set, pls set it during initialisation in a function with priority preferably at 6000000");}
    if(SGEXTN::ApplicationBase::InitSetup::organisationDomain == ""){SGEXTN::Containers::Crash::crash("application crashed during initialisation as SGEXTN::ApplicationBase::InitSetup::organisationDomain is not set, pls set it during initialisation in a function with priority preferably at 6000000, this does not need to be a real web URL");}
    QCoreApplication::setApplicationName(*SGEXTN::ApplicationBase::InitSetup::applicationName.private_data);
    QCoreApplication::setApplicationVersion(*SGEXTN::ApplicationBase::InitSetup::applicationVersion.private_data);
    QCoreApplication::setOrganizationName(*SGEXTN::ApplicationBase::InitSetup::organisationName.private_data);
    QCoreApplication::setOrganizationDomain(*SGEXTN::ApplicationBase::InitSetup::organisationDomain.private_data);
}

void SGEXTN::ApplicationBase::InitSetup::private_createConsoleApp(){
    if(SGEXTN::ApplicationBase::InitSetup::isConsoleApp == true){
        new QCoreApplication(SGEXTN::ApplicationBase::InitSetup::private_argc, SGEXTN::ApplicationBase::InitSetup::private_argv);
    }
}

void SGEXTN::ApplicationBase::InitSetup::private_runUserMain(){
    if(SGEXTN::ApplicationBase::InitSetup::isConsoleApp == true){
        if(SGEXTN::ApplicationBase::InitSetup::userMain == nullptr){SGEXTN::Containers::Crash::crash("application crashed during initialisation as SGEXTN::ApplicationBase::InitSetup::userMain is not set but a console app was requested, pls set it during initialisation in a function with priority preferably at 6000000");}
        SGEXTN::ApplicationBase::InitSetup::private_returnValue = SGEXTN::ApplicationBase::InitSetup::userMain(SGEXTN::ApplicationBase::InitSetup::private_argc, SGEXTN::ApplicationBase::InitSetup::private_argv);
        SGEXTN::ApplicationBase::InitSetup::private_runFinished = true;
    }
}
