#include <private_api/SGEXTN_InternalTest_StringTest.h>
#include <QFile>
#include <QByteArray>
#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_ApplicationBase_Debug.h>
#include <SGEXTN_ApplicationBase_UnicodeQuery.h>
#include <private_api/SGEXTN_Containers_Crash.h>

namespace {
SGEXTN::ApplicationBase::String readFile(const SGEXTN::ApplicationBase::String& filePath){
    if(filePath == ""){return "";}
    QByteArray data;
    QFile file(QString::fromUtf8(reinterpret_cast<const char*>(&filePath.private_data.byteAt(0)), filePath.byteLength()));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        data = file.readAll();
        file.close();
    }
    return SGEXTN::ApplicationBase::String(data.constData());
}

SGEXTN::Containers::Array<SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String>> unicodeDatabase(0x110000, SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String>(15));

void fillUnicodeDatabase(){
    SGEXTN::ApplicationBase::String dataString = readFile(":/SGEXTN_InternalTest/unicodedata.txt");
    SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> dataTable = dataString.split('\n');
    SGEXTN::Containers::Array<int> codePoint(dataTable.length());
    for(int i=0; i<dataTable.length(); i++){
        codePoint.at(i) = dataTable.at(i).substringCharactersLeft(dataTable.at(i).findFirstCharactersFromLeft(';')).parseToInt(nullptr, 16);
    }
    for(int i=0; i<dataTable.length(); i++){
        SGEXTN::Containers::Array<SGEXTN::ApplicationBase::String> fields = dataTable.at(i).split(';');
        if(fields.length() != 15){SG(fields.length());}
        if(fields.at(1).containsCharacters("First>")){
            int start = fields.at(0).parseToInt(nullptr, 16);
            int end = dataTable.at(i + 1).substringCharactersLeft(dataTable.at(i + 1).findFirstCharactersFromLeft(';')).parseToInt(nullptr, 16);
            for(int j=start; j<=end; j++){
                unicodeDatabase.at(j).at(0) = SGEXTN::ApplicationBase::String::stringFromInt(j, 16);
                for(int k=1; k<15; k++){
                    unicodeDatabase.at(j).at(k) = fields.at(k);
                }
            }
            i++;
        }
        else{
            int codePoint = fields.at(0).parseToInt(nullptr, 16);
            for(int j=0; j<15; j++){
                unicodeDatabase.at(codePoint).at(j) = fields.at(j);
            }
        }
    }
}
}

void SGEXTN::InternalTest::StringTest::testAll(){
    SGEXTN::InternalTest::StringTest::testUnicodeQuery();
    SGEXTN::InternalTest::StringTest::testCharacter();
    SGEXTN::InternalTest::StringTest::testString();
}

void SGEXTN::InternalTest::StringTest::testUnicodeQuery(){
    fillUnicodeDatabase();
    for(int i=0; i<0x110000; i++){
        int uppercase = i;
        if(unicodeDatabase.at(i).at(12) != ""){uppercase = unicodeDatabase.at(i).at(12).parseToInt(nullptr, 16);}
        if(uppercase != SGEXTN::ApplicationBase::UnicodeQuery::getUppercase(i)){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::UnicodeQuery check uppercase fail");}
    }
}

void SGEXTN::InternalTest::StringTest::testCharacter(){

}

void SGEXTN::InternalTest::StringTest::testString(){

}