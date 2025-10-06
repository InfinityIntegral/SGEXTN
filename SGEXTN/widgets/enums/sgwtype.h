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
        SequentialLongLabel,
        TextButton,
        IconButton,
        TextInput,
        LongInput,
        ScrollView,
        SequentialScrollView,
        ColourPicker,
        SingleTouchReceiver,
        MultiTouchReceiver,
        CustomRenderer,
        Undefined
    };
    static bool isBackground(SGWType::Type x);
    static bool isDisplayText(SGWType::Type x);
    static bool isButton(SGWType::Type x);
    static bool isInputField(SGWType::Type x);
};

#endif // SGWTYPE_H
