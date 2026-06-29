# SGEXTN README

This README is for the absolute latest, possibly unreleased version of SGEXTN that you see in this GitHub repository. For the latest stable version, refer to the releases section and the documentation accessible via [this link](https://infinityintegral.github.io/SGEXTN/readme/readme).

SGEXTN - Singaporean-made Extension to the C++ Core Language, currently work in progress, is written to provide an alternative to the Standard Template Library that is easy to use, more consistent between different platforms, faster to lint and compile, and provides a cross-platform framework for developing applications using the capabilities of Simple DirectMedia Layer 3 and AccessKit.

Current version of SGEXTN: v7.0.0

Published on: (none, work in progress)

I acknowledge that all technical and transferrable skills I used to work on this project are directly or indirectly taught to me by the Singapore Ministry of Education. I would like to thank my homeland for everything. Majulah Singapura. 🇸🇬

## List of modules

(This section will be written once v7.0.0 is complete)

## Setting up SGEXTN

(This section will be written once v7.0.0 is complete)

## Legal info

Copyright SG61 (2026) 05524F.sg

This product includes software developed at [05524F.sg](https://infinityintegral.github.io).

Remember to include my NOTICE and LICENSE file in your application; you can put it under LICENSES/05524F.sg/SGEXTN

The Apache 2.0 license forbids modifying the license itself, so the following is a suggestion not a legal requirement: You are encouraged to use the software to contribute to the National Interests of Singapore and the Singaporean and global public good. May the good we achieve, as one nation, be shared with the world.

SGEXTN uses the following dependencies:

* SGEXTN
    * Author: 05524F.sg
    * License: Apache 2.0
    * Source: https://github.com/InfinityIntegral/SGEXTN
    * Use: ownself
* parse-number-fxx-test-data
    * Author: Nigel Tao
    * License: Apache 2.0
    * Source: https://github.com/nigeltao/parse-number-fxx-test-data
    * Use: test cases for SGEXTN::CoreText::String number parsing
* Unicode data sets
    * Author: The Unicode Consortium
    * License: Unicode License v3
    * Source: https://www.unicode.org/Public/UCD/latest
    * Use: test cases for SGEXTN::CoreText::String and SGEXTN::CoreText::UnicodeQuery
* Sobol Sequence direction numbers
    * Author: Frances Y. Kuo and Stephen Joe
    * License: custom BSD-style license
    * Source: https://web.maths.unsw.edu.au/~fkuo/sobol/
    * Use: direction number initialisation for SGEXTN::SeerattraNum::SobolSequence
* Simple DirectMedia Layer 3 (SDL3)
    * Author: libsdl-org
    * License: zlib License
    * Source: https://github.com/libsdl-org/SDL
    * Use: (planned) abstraction over platform specific APIs
* SDL3 TTF
    * Author: libsdl-org
    * License: zlib License
    * Source: https://github.com/libsdl-org/SDL_ttf
    * Use: (planned) for parsing and using fonts
* SDL3 ShaderCross
    * Author: libsdl-org
    * License: zlib License
    * Source: https://github.com/libsdl-org/SDL_shadercross
    * Use: SingEmbed shader compilation and (planned) shader compilation at runtime
