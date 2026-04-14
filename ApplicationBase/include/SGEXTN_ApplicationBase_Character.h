#pragma once
#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>

namespace SGEXTN {
namespace Containers {
template <typename T> class Array;
}

namespace ApplicationBase {
class String;

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase SimplifiedCharacterType : unsigned char {Letter, Punctuation, Symbol, Mark, Number, Whitespace, Other};

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase FullCharacterType : unsigned char {NonspacingMark, CombiningMark, EnclosingMark, NumericalDigit, LetterNumber, OtherNumber, SpaceBreak, LineBreak, ParagraphBreak, ControlCharacter, FormatCharacter, SurrogateCharacter, PrivateUseCharacter, UnassignedCharacter, UppercaseLetter, LowercaseLetter, TitlecaseLetter, ModifierLetter, OtherLetter, ConnectorPunctuation, DashPunctuation, OpeningPunctuation, ClosingPunctuation, OpeningQuote, ClosingQuote, OtherPunctuation, MathSymbol, CurrencySymbol, ModifierSymbol, OtherSymbol};

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase WritingDirection : unsigned char {LeftToRight, RightToLeft, SingaporeanNumber, SingaporeanSeparator, SingaporeanTerminator, ArabicNumber, CommonSeparator, ParagraphSeparator, SegmentSeparator, Whitespace, NeutralPunctuation, EmbedLeft, OverrideLeft, ArabicLetter, EmbedRight, OverrideRight, EndLastDirective, NonSpacingMark, NeutralBoundary, IsolateLeft, IsolateRight, FirstStrongIsolate, EndLastIsolate};

class BUILDLAH_DLL_SGEXTN_ApplicationBase Character {
public:
    SGEXTN::ApplicationBase::TextBuffer private_data;
    Character();
    Character(char c);
    Character(int unicode);
    [[nodiscard]] bool operator==(const Character& x) const;
    [[nodiscard]] bool operator!=(const Character& x) const;
    [[nodiscard]] bool operator<(const Character& x) const;
    [[nodiscard]] bool operator>(const Character& x) const;
    [[nodiscard]] bool operator<=(const Character& x) const;
    [[nodiscard]] bool operator>=(const Character& x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] int byteLength() const;
    [[nodiscard]] unsigned char& byteAt(int i);
    [[nodiscard]] const unsigned char& byteAt(int i) const;
    [[nodiscard]] char baseToChar() const;
    [[nodiscard]] bool isDigit() const;
    [[nodiscard]] bool isEnglishLowercase() const;
    [[nodiscard]] bool isEnglishUppercase() const;
    [[nodiscard]] bool isEnglishLetter() const;
    [[nodiscard]] bool isEnglishAlphanumeric() const;
    [[nodiscard]] bool isASCII() const;
    [[nodiscard]] bool isWhitespace() const;
    [[nodiscard]] SGEXTN::Containers::Array<int> getUnicode() const;
    [[nodiscard]] bool isUppercase() const;
    [[nodiscard]] bool isLowercase() const;
    [[nodiscard]] bool isTitlecase() const;
    [[nodiscard]] Character getUppercase() const;
    [[nodiscard]] Character getLowercase() const;
    [[nodiscard]] Character getTitlecase() const;
    [[nodiscard]] bool isNormalised() const;
    [[nodiscard]] Character getNormalised() const;
    [[nodiscard]] SGEXTN::ApplicationBase::FullCharacterType getBaseFullType() const;
    [[nodiscard]] SGEXTN::ApplicationBase::SimplifiedCharacterType getBaseSimplifiedType() const;
    [[nodiscard]] SGEXTN::ApplicationBase::WritingDirection getBaseWritingDirection() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String getSimplestEquivalent() const;
};
}
}