#ifndef SGWTYPE_H
#define SGWTYPE_H

class SGWType
{
public:
    SGWType() = delete;
    enum Type{
        Root,
        Parent,
        StatusBar,
        BlankWidget,
        TextLabel,
        IconLabel,
        LongLabel,
        TextButton,
        IconButton,
        TextInput,
        LongInput,
        ScrollView,
        ColourPicker,
        GraphicsRenderer,
        TouchReceiver,
        FileUpload,
        FileDownload
    };
    static bool isDisplayText(SGWType::Type x);
    static bool isButton(SGWType::Type x);
    static bool isInputField(SGWType::Type x);
    static bool isFileDialog(SGWType::Type x);
};

#endif // SGWTYPE_H
