#pragma once

namespace SGEXTN {
namespace CoreText {
class String;

enum class BuildLah_SGEXTN_CoreText SimplifiedCharacterType : unsigned char {Letter, Punctuation, Symbol, Mark, Number, Whitespace, Other};

enum class BuildLah_SGEXTN_CoreText FullCharacterType : unsigned char {NonspacingCombiningMark, SpacingCombiningMark, EnclosingMark, DecimalDigit, LetterNumber, OtherNumber, SpaceBreak, LineBreak, ParagraphBreak, ControlCharacter, FormatCharacter, SurrogateCharacter, PrivateUseCharacter, UnassignedCharacter, UppercaseLetter, LowercaseLetter, TitlecaseLetter, ModifierLetter, OtherLetter, ConnectorPunctuation, DashPunctuation, OpeningPunctuation, ClosingPunctuation, OpeningQuote, ClosingQuote, OtherPunctuation, MathSymbol, CurrencySymbol, ModifierSymbol, OtherSymbol};

enum class BuildLah_SGEXTN_CoreText GraphemeSegmentationType : unsigned char {Return, NewLine, ControlCharacter, Extend, ZeroWidthJoiner, RegionalIndicator, Prepend, SpacingCombiningMark, HangulLeading, HangulVowel, HangulTrailing, HangulLeadingAndVowel, HangulLeadingAndVowelAndTrailing, Other};

enum class BuildLah_SGEXTN_CoreText GraphemeRuleRelatedType : unsigned char {None, Rule11Emoji, Rule9cConsonant, Rule9cExtend, Rule9cLinker};

class BuildLah_SGEXTN_CoreText UnicodeQuery {
public:
    [[nodiscard]] static int getUppercase(int c);
    [[nodiscard]] static int getLowercase(int c);
    [[nodiscard]] static int getTitlecase(int c);
    [[nodiscard]] static bool isWhitespace(int c);
    [[nodiscard]] static SGEXTN::CoreText::FullCharacterType getFullType(int c);
    [[nodiscard]] static SGEXTN::CoreText::SimplifiedCharacterType getSimplifiedType(int c);
    [[nodiscard]] static int getDecimalDigitValue(int c);
    [[nodiscard]] static float getNumericalValue(int c);
    [[nodiscard]] static SGEXTN::CoreText::GraphemeSegmentationType getGraphemeSegmentationType(int c);
    [[nodiscard]] static SGEXTN::CoreText::GraphemeRuleRelatedType getGraphemeRuleRelatedType(int c);
    [[nodiscard]] static SGEXTN::CoreText::String getEquivDecomposition(int c);
    [[nodiscard]] static SGEXTN::CoreText::String getCompatDecomposition(int c);
    [[nodiscard]] static int getCombiningMarkOrder(int c);
    [[nodiscard]] static int getBinaryRecomposition(int first, int second);
};
}
}
