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
namespace InternalTest {
class BuildLah_SGEXTN_InternalTest SeerattraNumTest {
public:
    static void testAll();
    static void testTrueRandom();
    static void testSimpleRandom();
    static void testDirectInteger();
    static void testDirectFloatingPoint();
    static void testUniformDistributionInteger();
    static void testUniformDistributionFloatingPoint();
};
}
}
