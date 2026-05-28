#pragma once

namespace SGEXTN {
namespace ApplicationBase {
class String;

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase SimplifiedCharacterType : unsigned char {Letter, Punctuation, Symbol, Mark, Number, Whitespace, Other};

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase FullCharacterType : unsigned char {NonspacingCombiningMark, SpacingCombiningMark, EnclosingMark, DecimalDigit, LetterNumber, OtherNumber, SpaceBreak, LineBreak, ParagraphBreak, ControlCharacter, FormatCharacter, SurrogateCharacter, PrivateUseCharacter, UnassignedCharacter, UppercaseLetter, LowercaseLetter, TitlecaseLetter, ModifierLetter, OtherLetter, ConnectorPunctuation, DashPunctuation, OpeningPunctuation, ClosingPunctuation, OpeningQuote, ClosingQuote, OtherPunctuation, MathSymbol, CurrencySymbol, ModifierSymbol, OtherSymbol};

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase GraphemeSegmentationType : unsigned char {Return, NewLine, ControlCharacter, Extend, ZeroWidthJoiner, RegionalIndicator, Prepend, SpacingCombiningMark, HangulLeading, HangulVowel, HangulTrailing, HangulLeadingAndVowel, HangulLeadingAndVowelAndTrailing, Other};

enum class BUILDLAH_DLL_SGEXTN_ApplicationBase GraphemeRuleRelatedType : unsigned char {None, Rule11Emoji, Rule9cConsonant, Rule9cExtend, Rule9cLinker};

class BUILDLAH_DLL_SGEXTN_ApplicationBase UnicodeQuery {
public:
    [[nodiscard]] static int getUppercase(int c);
    [[nodiscard]] static int getLowercase(int c);
    [[nodiscard]] static int getTitlecase(int c);
    [[nodiscard]] static bool isWhitespace(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::FullCharacterType getFullType(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::SimplifiedCharacterType getSimplifiedType(int c);
    [[nodiscard]] static int getDecimalDigitValue(int c);
    [[nodiscard]] static float getNumericalValue(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::GraphemeSegmentationType getGraphemeSegmentationType(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::GraphemeRuleRelatedType getGraphemeRuleRelatedType(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::String getEquivDecomposition(int c);
    [[nodiscard]] static SGEXTN::ApplicationBase::String getCompatDecomposition(int c);
    [[nodiscard]] static int getCombiningMarkOrder(int c);
    [[nodiscard]] static int getBinaryRecomposition(int first, int second);
};
}
}