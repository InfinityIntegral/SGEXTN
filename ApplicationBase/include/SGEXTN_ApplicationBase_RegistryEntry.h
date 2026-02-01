#pragma once

namespace SGEXTN {
namespace Containers { template <typename T, typename Comparator> class PriorityQueue; }
namespace ApplicationBase {
class RegistryEntryComparator;

class BUILDLAH_DLL_SGEXTN_ApplicationBase RegistryEntry {
public:
    RegistryEntry() = default;
    RegistryEntry(SGEXTN::Containers::PriorityQueue<RegistryEntry, SGEXTN::ApplicationBase::RegistryEntryComparator>*& functionQueue, int priority, void (*attachedFunction)());
    int private_priority;
    void (*private_attachedFunction)();
};

class BUILDLAH_DLL_SGEXTN_ApplicationBase RegistryEntryComparator {
public:
    bool operator()(const SGEXTN::ApplicationBase::RegistryEntry& a, const SGEXTN::ApplicationBase::RegistryEntry& b);
};
}
}
