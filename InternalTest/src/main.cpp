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

#include <SGEXTN/InternalTest/private_api/ContainersTest.h>
#include <SGEXTN/InternalTest/private_api/MathTest.h>
#include <SGEXTN/InternalTest/private_api/UtilitiesTest.h>
#include <SGEXTN/InternalTest/private_api/CoreTextTest.h>
#include <SGEXTN/InternalTest/private_api/ExternalTest.h>
#include <SGEXTN/InternalTest/private_api/DebugTest.h>
#include <SGEXTN/InternalTest/private_api/SeerattraNumTest.h>
#include <SGEXTN/CoreText/Debug.h>

int main(int /*argc*/, char** /*argv*/){
    SGEXTN::InternalTest::ContainersTest::testAll();
    SGEXTN::InternalTest::MathTest::testAll();
    SGEXTN::InternalTest::UtilitiesTest::testAll();
    SGEXTN::InternalTest::CoreTextTest::testAll();
    SGEXTN::InternalTest::ExternalTest::testAll();
    SGEXTN::InternalTest::DebugTest::runTest();
    SGEXTN::InternalTest::SeerattraNumTest::testAll();
    SG("all tests pass");
}
