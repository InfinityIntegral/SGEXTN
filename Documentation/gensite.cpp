#include <string>
#include <array>

void init();
std::string header;
std::string footer;
std::string style;
std::string page404;
std::string pageContact;
std::string pageSetup;
std::string pageClassInfo;
std::string pageHome;
std::array<std::string, 4> pageTemplate;

std::string genSiteMap(std::string input)

int main(){
    init();
}

void init(){
    
    header = R"(
<div>
<button class="button" style="width: 100%;" onclick="location.href='/'">
<img src="https://raw.githubusercontent.com/InfinityIntegral/InfinityIntegral/main/flagemoji.png" style="vertical-align: middle; height: 1.5rem; image-rendering: auto;"> SGEXTN Documentation <img src="https://raw.githubusercontent.com/InfinityIntegral/InfinityIntegral/main/flagemoji.png" style="vertical-align: middle; height: 1.5rem; image-rendering: auto;">
</button>
</div>
)";
    
    footer = R"(
<div>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<p class="label">©2025 05524F.sg (Singapore)</p>
<p class="label"><a class="link" href="./contact.html">report a bug in SGEXTN or contact 05524F</a></p>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
</div>
)";
    
    style = R"(
<link rel="icon" href="icon.png" type="image/png">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>

@font-face {
	font-family: "SingScript.sg";
	src: url("SingScript.sg")format("truetype");
	font-weight: normal;
	font-style: normal;
}

:root {
	--c0: rgb(0, 0, 0);
	--c1: rgb(64, 0, 50);
	--c2: rgb(128, 0, 100);
	--c3: rgb(191, 0, 150);
	--c4: rgb(255, 0, 200);
	--c5: rgb(255, 64, 214);
	--c6: rgb(255, 128, 227);
	--c7: rgb(255, 191, 241);
	--c8: rgb(255, 255, 255);
}

*{
        font-family: "SingScript.sg";
	max-width: 100%;
	word-break: break-word;
	-webkit-text-size-adjust: 100%;
	-ms-text-size-adjust: 100%;
}

.title {
	color: var(--c4);
	background-color: var(--c8);
	font-size: 3.5rem;
	margin: 0;
	font-weight: normal;
}
.title::selection {
	color: var(--c8);
	background-color: var(--c4);
	font-size: 3.5rem;
	margin: 0;
	font-weight: normal;
}

.halftitle {
	color: var(--c4);
	background-color: var(--c8);
	font-size: 2.5rem;
	margin: 0;
	font-weight: normal;
}
.halftitle::selection {
	color: var(--c8);
	background-color: var(--c4);
	font-size: 2.625rem;
	margin: 0;
	font-weight: normal;
}

.label {
	color: var(--c4);
	background-color: var(--c8);
	font-size: 1.75rem;
	margin: 0;
	white-space: pre-wrap;
}
.label::selection {
	color: var(--c8);
	background-color: var(--c4);
	font-size: 1.75rem;
	margin: 0;
	white-space: pre-wrap;
}

.link {
	color: var(--c2);
	background-color: var(--c8);
	text-decoration: underline;
}
.link:hover {
	color: var(--c2);
	background-color: var(--c7);
	text-decoration: underline;
}
.link:active {
	color: var(--c2);
	background-color: var(--c6);
	text-decoration: underline;
}
.link::selection {
	color: var(--c8);
	background-color: var(--c4);
	text-decoration: underline;
}

.button {
	color: var(--c8);
	background-color: var(--c4);
	font-size: 1.75rem;
	border: none;
}
.button:hover {
	color: var(--c7);
	background-color: var(--c3);
	font-size: 1.75rem;
	border: none;
}
.button:active {
	color: var(--c6);
	background-color: var(--c2);
	font-size: 1.75rem;
	border: none;
}
.button::selection {
	color: var(--c4);
	background-color: var(--c8);
	font-size: 1.75rem;
	border: none;
}

.input {
	color: var(--c8);
	background-color: var(--c4);
	font-size: 1.75rem;
	border: none;
	outline: none;
	text-align: center;
}
.input:hover {
	color: var(--c7);
	background-color: var(--c3);
	font-size: 1.75rem;
	border: none;
	outline: none;
	text-align: center;
}
.input:focus {
	color: var(--c6);
	background-color: var(--c2);
	font-size: 1.75rem;
	border: none;
	outline: none;
	text-align: center;
}
.input::selection {
	color: var(--c4);
	background-color: var(--c8);
	font-size: 1.75rem;
	border: none;
	outline: none;
	text-align: center;
}

</style>
)";
    
    pageContact = R"(
<h1 class="title">Contact 05524F</h1>
<p class="label">&#x9;You should contact 05524F immediately if anything in SGEXTN is not working as expected according to the documentation or if there are errors in the documentation. You can also suggest features to be added to SGEXTN, but 05524F is unlikely to accept your request unless it is really good. SGEXTN is licensed under LGPL, so you may change the internals or add new components if you want as long as you open source your changes or write to 05524F to apply for exemption from the license (more info below).<br>&#x9;You may contact 05524F by email or by Instagram. Note that your Instagram friend request will only be accepted if you know Student 05524F personally, otherwise, only email contact is allowed.</p>
<p class="label">email: <a class="link" href="mailto:infinityintegral333@gmail.com">infinityintegral333@gmail.com</a></p>
<p class="label">Instagram: <a class="link" href="https://www.instagram.com/infinityintegral.sg/?hl=en">@infinityintegral.sg</a><br>&nbsp;</p>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<h1 class="title">Why 05524F</h1>
<p class="label">&#x9;The name of 05524F comes from Student 05524F, PSLE index number of the person writing code for 05524F. On official copyright statements such as those in licenses, the name 05524F.sg is written to credit Singapore.<br>&nbsp;</p>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<h1 class="title">Legal info</h1>
<p class="label">&#x9;SGEXTN is licensed under <a class="link" href="https://opensource.org/license/lgpl-3-0">LGPL v3</a> (Lesser General Public License). This essentially means that you do not have to open source your work if using SGEXTN normally but should do so if you changed SGEXTN internals. Note that the SGUCentralManagement class is not considered SGEXTN internals and can be freely edited.<br>&#x9;Qt's license is completely separate from the SGEXTN license. You must follow their license strictly and 05524F cannot exempt you from the Qt license.<br>&#x9;If you changed SGEXTN but do not want to open source your work, you must get an exemption from 05524F first. 05524F is likely to grant license exemptions to residents and citizens of Singapore but the exemption is revoked automatically if you move to somewhere else or change your citizenship. 05524F can also grant license exemptions to projects that prominently feature the letters "SG" or "sg" in their names, but the exemption is revoked automatically if the project is renamed. In any case, 05524F must explicitly authorise exemptions and it only applies to the SGEXTN license, not the Qt license.<br>&nbsp;</p>
)";
    
    pageSetup = R"(
<h1 class="title">Setting up SGEXTN</h1>
<p class="label">&#x9;SGEXTN uses <a class="link" href="https://www.qt.io/">Qt</a> Quick extensively and can only be used in a Qt project. Qt version 6.9 and above is recommended.<br>&#x9;To use SGEXTN, copy the entire SGEXTN folder from the <a class="link" href="https://github.com/InfinityIntegral/SGEXTN">GitHub repository</a> into the root folder of your project which should contain your project file (.pro). To include it, write the line<br><br>&#x9;include(SGEXTN/SGEXTN.pri)<br><br> at the top of your project file (.pro). After that, go to the file SGEXTN/userDefinedClasses/sgucentralmanagement.cpp, read through the comments in the file and customise whatever is needed. Do not change anything in the SGEXTN folder unless specified by the file.<br>&#x9;Your custom code should be outside the SGEXTN folder. Classes in your custom code should have the prefix SGC. The first word in the names of renderer classes should be "Render".<br>&nbsp;</p>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<h1 class="title">File prefixes</h1>
<p class="label">SGEXTN uses file prefixes to mean different things.<br>&#x9;SGX: SGEXTN classes not using SGWidget in any way<br>&#x9;SGW: SGEXTN classes using SGWidget and the SGWidget module itself<br>&#x9;SGU: customisable part of SGEXTN, can be changed by user<br>&#x9;SGC: user's custom code<br>Names of all renderer classes should start with the word "Render".<br>&nbsp;</p>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<h1 class="title">Extending SGEXTN</h1>
<p class="label">&#x9;You can extend SGEXTN by adding renderers. Renderers can be used to display shader output, non rectangular UI, and large amounts of UI.<br>To build a renderer, you need the following:<br>&#x9;- a vertex shader (.vert) in GLSL, built using QSB into a Qt Shader Binary (.qsb) for deployment across all rendering backends<br>&#x9;- a fragment shader (.frag) in GLSL, built using QSB into a Qt Shader Binary (.qsb) for deployment across all rendering backends.<br>&#x9;- a QML file (.qml) describing the QML Component<br>&#x9;- C++ header (.h) and source (.cpp) files for the material<br>&#x9;- C++ header (.h) and source (.cpp) files for the shader, the shader must upload uniform data<br>&#x9;- C++ header (.h) and source (.cpp) files for the QQuickItem, this must set up the QQuickItem appropriately for rendering by Qt Quick<br>&#x9;- C++ header (.h) and source (.cpp) files for the SGWidget, this must inherit SGWCustomRenderer and set up the SGWidget appropriately<br>&#x9;- the type must be registered with the QML system, see comments on top of the dedicated function in SGEXTN/userDefinedClasses/sgucentralmanagement.cpp for more information<br><br>Refer to the SGEXTN/colourpickerrendering/huechoice folder for an example.<br>&nbsp;</p>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<h1 class="title">UIB-DINB philosophy</h1>
<p class="label">&#x9;The SGEXTN framework is designed with the UIB-DINB philosophy in mind. UIB-DINB is "user is blur, developer is not blur", which is Singlish for "user gets confused, developer will not get confused".<br>&#x9;You, as a developer, are expected to be able to read SGEXTN documentation and source code if needed. You are expected to not be afraid of manual memory management, raw pointers, and function pointers. You should prioritise efficiency and user experience in your applications over time taken to build or ease of development. SGEXTN does not attempt to protect you from complexity excessively. For example, SGEXTN does not follow encapsulation and abstraction strictly inside the SGWidget module and does not follow these principles at all outside the module. You are discouraged from using shortcuts such as auto type because that may prevent you from fully understanding and optimising the code.<br>&#x9;You should design UI such that there is no way for the user to crash your app. If data entered is invalid, the user should be informed appropriately. Refer to the SingCorrect configuration page for what that looks like.<br>&nbsp;</p>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<h1 class="title">Why SGEXTN</h1>
<p class="label">&#x9;SGEXTN allows you to use Qt Quick as a GUI toolkit without the annoying bits via SGWidget, such as QML declarative UI, JavaScript, signal-slot etc. This makes it much easier to use for someone familiar with C++ and does not know anything about JavaScript and related nonsense. Apart from SGWidget, there are also other things that most applications would need, such as file reading, file writing, and the use of colours.<br>&#x9;Using SGEXTN to build apps feel like QWidget but without the signal-slot callbacks. Also, make sure to become familiar with function pointer syntax first before using SGEXTN, because SGEXTN callbacks are raw function pointers.</p>
<h2 class="halftitle">QML?</h2>
<p class="label">&#x9;QML is the Qt Quick way of writing declarative UI using JSON syntax and with use of JavaScript for functions. Qt intends this to be similar to frontend development in website building. However, if one just want to write C++ and see widgets on screen, that would not work. Also, writing even tiny functions in JavaScript means dealing with all of JavaScript's nonsense, such as literally no types. By using SGEXTN's SGWidget system, you would not need a single line of QML when building UI.</p>
<h2 class="halftitle">signal-slot?</h2>
<p class="label">&#x9;Signal-slot is Qt's system for building callback functions. In Qt 6, they are essentially function pointers, which is good. However, using them requires the Q_OBJECT macro and MetaObject Compiler (MOC) processing, which increases compile time. SGEXTN abstracts that away by using raw function pointers for callbacks attached to timers (SGXTimer) and interactive UI elements including buttons (SGWButton subclasses) and input fields (SGWInput subclasses).</p>
<h2 class="halftitle">What if I want Qt stuff?</h2>
<p class="label">&#x9;SGEXTN abstracts Qt stuff without disabling them. So if you really want to use Qt stuff, you can do that normally.<br>&nbsp;</p>
)";
    
    pageClassInfo = R"(
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<p class="label">&#x9;Only properties, functions, and classes intended for public use have documentation. Your code autocompletion tool may provide suggestions that are not documented. You are discouraged from using these undocumented properties, functions, and classes unless you have read the source code and understand what they do.<br>&#x9;All information on this documentation page are only valid for SGEXTN version 5.1.0, future versions may have new features added or removed. For documentation of past versions, pls see the documentation bundled with the release.<br>&nbsp;</p>
)";
    
    pageHome = R"(
<h1 class="title">What is SGEXTN?</h1>
<p class="label">&#x9;SGEXTN is a framework built on top of <a class="link" href="https://www.qt.io/">Qt</a> Quick. It provides essential functionality for building apps, such as a colour struct and file system access. The SGWidget module provides a full GUI toolkit to build UI without writing a single line of QML. SGEXTN also does not use signal-slot, instead callback functions are implemented using function pointers.<br>&#x9;Note that documentation is only provided for the latest version. For earlier documentation, pls host the Documentation folder of your release yourself on <a class="link" href="https://www.apachefriends.org/">XAMPP Apache</a>.<br>Below is the full list of all SGEXTN classes with links to their documentation pages.</p>
<p class="label"><a class="link" href="./setup.html">how to set up SGEXTN</a></p>
<p class="label"><br></p>
<div style="width: 100%; height: 0.25em; background-color: var(--c4);"></div>
<p class="label">list of all classes that you can use inside SGEXTN 5.1.0:</p>
<p class="label" id="sitemap"></p>
)";
    
    pageTemplate = {"\n<!DOCTYPE html>\n<html lang=\"en-SG\">\n<head>\n<meta charset=\"UTF-8\">\n<title>", "</title>\n", "\n</head>\n<body>\n", "\n</body>\n</html>\n"};
    
    }
    
    std::string genSiteMap(std::string input){
        std::string output = "";
        int indent = 0;
        output += "<p class=\"label\">";
        std::stringstream stream(input);
        std::string s = "";
        while(std::getline(stream, s)){
            if(s == "<"){indent--;}
            else if(s == ">"){indent++;}
            else if(s.length() > 0 && s[0] == '/'){
                output += "\n";
                for(int i=0; i<indent; i++){output += "&#x9;";}
                output += s.substr(1);
            }
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
    
}
























































