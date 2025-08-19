#include <string>
#include <sstream>
#include <emscripten/bind.h>

// emcc gensitemap.cpp -O3 -s MODULARIZE=1 -s EXPORT_NAME="SiteMapModule" -o site_map_module.js --bind

std::string genSiteMap(std::string input){
    std::string output = "";
    int indent = 0;
    output += "<p class=\"label\">";
    std::stringstream stream(input);
    std::string s = "";
    while(stream >> s){
        if(s == "<"){indent--;}
        else if(s == ">"){indent++;}
        else{
            output += "\n";
            for(int i=0; i<indent; i++){output += "&#x9;";}
            std::string sl = s;
            for(int i=0; i<sl.length(); i++){
                if(sl[i] >= 'A' && sl[i] <= 'Z'){sl[i] += ('a' - 'A');}
            }
            std::string link = "\"./classinfo?classname=" + sl + "\"";
            output += ("<a class=\"link\" href=" + link + ">");
            output += s;
            output += "</a>";
        }
    }
    output += "\n</p>";
    return output;
}

EMSCRIPTEN_BINDINGS(site_map_module){
    emscripten::function("genSiteMap", &genSiteMap);
}
