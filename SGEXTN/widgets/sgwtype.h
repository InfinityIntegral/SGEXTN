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
        PageBackground,
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
        CustomRenderer,
        Undefined
    };
    static bool isDisplayText(SGWType::Type x);
    static bool isButton(SGWType::Type x);
    static bool isInputField(SGWType::Type x);
};

#endif // SGWTYPE_H
