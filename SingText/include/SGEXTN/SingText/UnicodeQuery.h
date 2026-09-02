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

namespace SGEXTN::SingText {
class String;

enum class SimplifiedCharacterType : unsigned char {
    Letter = 1,
    Punctuation = 2,
    Symbol = 3,
    Mark = 4,
    Number = 5,
    Whitespace = 6,
    Other = 7
};

enum class FullCharacterType : unsigned char {
    NonspacingCombiningMark = 0x01,
    SpacingCombiningMark = 0x02,
    EnclosingMark = 0x03,
    DecimalDigit = 0x11,
    LetterNumber = 0x12,
    OtherNumber = 0x13,
    SpaceBreak = 0x21,
    LineBreak = 0x22,
    ParagraphBreak = 0x23,
    ControlCharacter = 0x31,
    FormatCharacter = 0x32,
    SurrogateCharacter = 0x33,
    PrivateUseCharacter = 0x34,
    UnassignedCharacter = 0x35,
    UppercaseLetter = 0x41,
    LowercaseLetter = 0x42,
    TitlecaseLetter = 0x43,
    ModifierLetter = 0x44,
    OtherLetter = 0x45,
    ConnectorPunctuation = 0x51,
    DashPunctuation = 0x52,
    OpeningPunctuation = 0x53,
    ClosingPunctuation = 0x54,
    OpeningQuote = 0x55,
    ClosingQuote = 0x56,
    OtherPunctuation = 0x57,
    MathSymbol = 0x61,
    CurrencySymbol = 0x62,
    ModifierSymbol = 0x63,
    OtherSymbol = 0x64
};

enum class GraphemeSegmentationType : unsigned char {
    Return = 0x01,
    NewLine = 0x02,
    ControlCharacter = 0x11,
    Extend = 0x21,
    ZeroWidthJoiner = 0x03,
    RegionalIndicator = 0x31,
    Prepend = 0x22,
    SpacingCombiningMark = 0x12,
    HangulLeading = 0x41,
    HangulVowel = 0x42,
    HangulTrailing = 0x43,
    HangulLeadingAndVowel = 0x44,
    HangulLeadingAndVowelAndTrailing = 0x45,
    Other = 0x51
};

enum class GraphemeRuleRelatedType : unsigned char {
    None = 1,
    Rule11Emoji = 2,
    Rule9cConsonant = 3,
    Rule9cExtend = 4,
    Rule9cLinker = 5
};

class BuildLah_SGEXTN_SingText UnicodeQuery {
public:
    [[nodiscard]] static int getUppercase(int c);
    [[nodiscard]] static int getLowercase(int c);
    [[nodiscard]] static int getTitlecase(int c);
    [[nodiscard]] static bool isWhitespace(int c);
    [[nodiscard]] static SGEXTN::SingText::FullCharacterType getFullType(int c);
    [[nodiscard]] static SGEXTN::SingText::SimplifiedCharacterType getSimplifiedType(int c);
    [[nodiscard]] static int getDecimalDigitValue(int c);
    [[nodiscard]] static float getNumericalValue(int c);
    [[nodiscard]] static SGEXTN::SingText::GraphemeSegmentationType getGraphemeSegmentationType(int c);
    [[nodiscard]] static SGEXTN::SingText::GraphemeRuleRelatedType getGraphemeRuleRelatedType(int c);
    [[nodiscard]] static SGEXTN::SingText::String getEquivDecomposition(int c);
    [[nodiscard]] static SGEXTN::SingText::String getCompatDecomposition(int c);
    [[nodiscard]] static int getCombiningMarkOrder(int c);
    [[nodiscard]] static int getBinaryRecomposition(int first, int second);
};
}
