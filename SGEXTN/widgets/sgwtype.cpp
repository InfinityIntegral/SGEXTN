#include "sgwtype.h"

bool SGWType::isDisplayText(SGWType::Type x){
    if(x == SGWType::TextLabel || x == SGWType::IconLabel || x == SGWType::LongLabel){return true;}
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

bool SGWType::isFileDialog(SGWType::Type x){
    if(x == SGWType::FileDownload || x == SGWType::FileUpload){return true;}
    return false;
}
