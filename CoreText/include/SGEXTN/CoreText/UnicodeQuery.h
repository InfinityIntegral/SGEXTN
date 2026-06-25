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
