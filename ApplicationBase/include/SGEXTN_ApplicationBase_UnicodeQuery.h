#pragma once

namespace SGEXTN {
namespace ApplicationBase {
enum class BUILDLAH_DLL_SGEXTN_ApplicationBase SimplifiedCharacterType : unsigned char {Letter, Punctuation, Symbol, Mark, Number, Whitespace, Other};

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase FullCharacterType : unsigned char {NonspacingCombiningMark, SpacingCombiningMark, EnclosingMark, DecimalDigit, LetterNumber, OtherNumber, SpaceBreak, LineBreak, ParagraphBreak, ControlCharacter, FormatCharacter, SurrogateCharacter, PrivateUseCharacter, UnassignedCharacter, UppercaseLetter, LowercaseLetter, TitlecaseLetter, ModifierLetter, OtherLetter, ConnectorPunctuation, DashPunctuation, OpeningPunctuation, ClosingPunctuation, OpeningQuote, ClosingQuote, OtherPunctuation, MathSymbol, CurrencySymbol, ModifierSymbol, OtherSymbol};

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase WritingDirection : unsigned char {LeftToRight, RightToLeft, SingaporeanNumber, SingaporeanSeparator, SingaporeanTerminator, ArabicNumber, CommonSeparator, ParagraphSeparator, SegmentSeparator, Whitespace, NeutralPunctuation, EmbedLeft, OverrideLeft, ArabicLetter, EmbedRight, OverrideRight, EndLastDirective, NonSpacingMark, NeutralBoundary, IsolateLeft, IsolateRight, FirstStrongIsolate, EndLastIsolate};

class BUILDLAH_DLL_SGEXTN_ApplicationBase UnicodeQuery {
public:
    [[nodiscard]] static int getUppercase(int c);
    [[nodiscard]] static int getLowercase(int c);
    [[nodiscard]] static int getTitlecase(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::FullCharacterType getFullType(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::SimplifiedCharacterType getSimplifiedType(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::WritingDirection getWritingDirection(int c);
    // add script of origin, numerical value, decimal digit value, visual digit value, mirror, unicode block
};
}
}