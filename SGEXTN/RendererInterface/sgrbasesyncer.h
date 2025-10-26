#ifndef SGRBASESYNCER_H
#define SGRBASESYNCER_H

class SGRBaseRenderer;
class SGRBaseSyncer
{
public:
    SGRBaseSyncer() = default;
    SGRBaseSyncer(const SGRBaseSyncer&) = delete;
    SGRBaseSyncer& operator=(const SGRBaseSyncer&) = delete;
    SGRBaseSyncer(SGRBaseSyncer&&) = delete;
    SGRBaseSyncer& operator=(SGRBaseSyncer&&) = delete;
    virtual ~SGRBaseSyncer() = default;
    virtual void sync(SGRBaseRenderer* renderControl) = 0;
};

#endif // SGRBASESYNCER_H
