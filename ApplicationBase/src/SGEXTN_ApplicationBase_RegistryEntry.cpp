#include <SGEXTN_ApplicationBase_RegistryEntry.h>
#include <SGEXTN_Containers_PriorityQueue.h>

SGEXTN::ApplicationBase::RegistryEntry::RegistryEntry(SGEXTN::Containers::PriorityQueue<SGEXTN::ApplicationBase::RegistryEntry, SGEXTN::ApplicationBase::RegistryEntryComparator>*& functionQueue, int priority, void (*attachedFunction)()){
    private_priority = priority;
    private_attachedFunction = attachedFunction;
    if(functionQueue == nullptr){
        functionQueue = new SGEXTN::Containers::PriorityQueue<SGEXTN::ApplicationBase::RegistryEntry, SGEXTN::ApplicationBase::RegistryEntryComparator>();
    }
    (*functionQueue).push(*this);
}

bool SGEXTN::ApplicationBase::RegistryEntryComparator::operator()(const SGEXTN::ApplicationBase::RegistryEntry& a, const SGEXTN::ApplicationBase::RegistryEntry& b){
    return (a.private_priority < b.private_priority);
}
