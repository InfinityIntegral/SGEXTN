/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/Span.h>
#include <SGEXTN/Containers/Serialise.h>

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::DirectRandomInstanceLocator(bool useGlobal) : ownsRng_(useGlobal == false), rng_(SGEXTN::SeerattraNum::DirectRandom::createRng(useGlobal)){}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::DirectRandomInstanceLocator(const SGEXTN::SeerattraNum::DirectRandom& rng) : ownsRng_(true), rng_(new SGEXTN::SeerattraNum::DirectRandom(rng)){}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::DirectRandomInstanceLocator(const DirectRandomInstanceLocator& x) : ownsRng_(x.ownsRng_), rng_(x.rng_){
    if(ownsRng_ == true){rng_ = new SGEXTN::SeerattraNum::DirectRandom(*x.rng_);}
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator& SGEXTN::SeerattraNum::DirectRandomInstanceLocator::operator=(const DirectRandomInstanceLocator& x){
    if(this == &x){return (*this);}
    if(ownsRng_ == true){delete rng_;}
    ownsRng_ = x.ownsRng_;
    if(ownsRng_ == false){rng_ = x.rng_;}
    else{rng_ = new SGEXTN::SeerattraNum::DirectRandom(*x.rng_);}
    return (*this);
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::DirectRandomInstanceLocator(DirectRandomInstanceLocator&& x) noexcept : ownsRng_(x.ownsRng_), rng_(x.rng_){
    x.ownsRng_ = false;
    x.rng_ = nullptr;
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator& SGEXTN::SeerattraNum::DirectRandomInstanceLocator::operator=(DirectRandomInstanceLocator&& x) noexcept {
    if(this == &x){return (*this);}
    if(ownsRng_ == true){delete rng_;}
    ownsRng_ = x.ownsRng_;
    rng_ = x.rng_;
    x.ownsRng_ = false;
    x.rng_ = nullptr;
    return (*this);
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::~DirectRandomInstanceLocator(){
    if(ownsRng_ == true){delete rng_;}
}

SGEXTN::SeerattraNum::DirectRandom& SGEXTN::SeerattraNum::DirectRandomInstanceLocator::operator*(){
    SGEXTN::SeerattraNum::DirectRandom* temp = rng_;
    rng_ = temp;
    return (*rng_);
}

const SGEXTN::SeerattraNum::DirectRandom& SGEXTN::SeerattraNum::DirectRandomInstanceLocator::operator*() const {
    return (*rng_);
}

bool SGEXTN::SeerattraNum::DirectRandomInstanceLocator::sendOut(const SGEXTN::SeerattraNum::DirectRandomInstanceLocator& x, SGEXTN::Containers::Span<unsigned char> data){
    if(x.ownsRng_ == false){
        for(int i=0; i<37; i++){
            data.at(i) = static_cast<unsigned char>(0);
        }
        data.at(32) = static_cast<unsigned char>(0xff);
        return true;
    }
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandom>::sendOut((*x.rng_), data);
}

bool SGEXTN::SeerattraNum::DirectRandomInstanceLocator::sendIn(SGEXTN::SeerattraNum::DirectRandomInstanceLocator& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.at(32) == static_cast<unsigned char>(0xff)){
        for(int i=0; i<37; i++){
            if(i != 32 && data.at(i) != static_cast<unsigned char>(0)){return false;}
        }
        x = SGEXTN::SeerattraNum::DirectRandomInstanceLocator(true);
        return true;
    }
    SGEXTN::SeerattraNum::DirectRandom rng;
    const bool isValid = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandom>::sendIn(rng, data);
    if(isValid == false){return false;}
    x = SGEXTN::SeerattraNum::DirectRandomInstanceLocator(rng);
    return true;
}

int SGEXTN::SeerattraNum::DirectRandomInstanceLocator::size(){
    return 37;
}

bool SGEXTN::SeerattraNum::DirectRandomInstanceLocator::isUsingGlobal() const {
    return (ownsRng_ == false);
}
