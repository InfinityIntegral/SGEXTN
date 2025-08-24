#include "sgwtype.h"

bool SGWType::isBackground(SGWType::Type x){
    if(x == SGWType::PageBackground || x == SGWType::ScrollView || x == SGWType::SequentialScrollView){return true;}
    return false;
}

bool SGWType::isDisplayText(SGWType::Type x){
    if(x == SGWType::TextLabel || x == SGWType::IconLabel || x == SGWType::LongLabel || x == SGWType::SequentialLongLabel){return true;}
    return false;
}

bool SGWType::isButton(SGWType::Type x){
    if(x == SGWType::TextButton || x == SGWType::IconButton){return true;}
    return false;
}

bool SGWType::isInputField(SGWType::Type x){
    if(x == SGWType::TextInput || x == SGWType::LongInput){return true;}
    return false;
}
