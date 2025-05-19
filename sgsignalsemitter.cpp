#include "sgsignalsemitter.h"

SGSignalsEmitter::SGSignalsEmitter(){

}

void SGSignalsEmitter::sendsignals(){
    emit (*this).updatescreen();
}
