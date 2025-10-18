![image of Singapore flag emoji](flag.png)

# SGEXTN ("SG" Extension for C++ and Qt)

I know we'll build a new world, a world of hope for ever after...

(reference to my [profile](https://github.com/InfinityIntegral) README)

## About this project

Note that SGEXTN can also be referred to as "SG Extension" or "The Singaporean Extension". However, do not refer to SGEXTN as "SGWidget", "SGX" or "SGW". When speaking about SGEXTN, read the name as "SG Extension".

### Contents

- [About this project](#about-this-project)
- [Contents](#contents)
	- [UIB-DINB philosophy](#uib-dinb-philosophy)
	- [Why SGEXTN?](#why-sgextn)
	- [Documentation](#documentation)
	- [Demo app WORK IN PROGRESS](#demo-app)
	- [Setting up SGEXTN](#setting-up-sgextn)
	- [Extending SGEXTN](#extending-sgextn)
	- [File prefixes](#file-prefixes)
- [Completed Features](#completed-features)
- [Credits](#credits)
- [Contributing](#contributing)
- [Contact me](#contact-me)
- [Am I blur?](#am-i-blur)

### UIB-DINB philosophy

The SGEXTN framework is designed with the UIB-DINB philosophy in mind. UIB-DINB is "user is blur, developer is not blur", which is Singlish for "user gets confused, developer will not get confused".

You, as a developer, are expected to be able to read SGEXTN documentation and source code if needed. You are expected to not be afraid of manual memory management, raw pointers, and function pointers. You should prioritise efficiency and user experience in your applications over time taken to build or ease of development. SGEXTN does not attempt to protect you from complexity excessively. For example, SGEXTN does not follow encapsulation and abstraction strictly inside the SGWidget module and does not follow these principles at all outside the module. You are discouraged from using shortcuts such as auto type because that may prevent you from fully understanding and optimising the code.

You should design UI such that there is no way for the user to crash your app. If data entered is invalid, the user should be informed appropriately. Refer to the SingCorrect configuration page for what that looks like.

### Why SGEXTN

SGEXTN allows you to use Qt Quick as a GUI toolkit without the annoying bits via SGWidget, such as QML declarative UI, JavaScript, signal-slot etc. This makes it much easier to use for someone familiar with C++ and does not know anything about JavaScript and related nonsense. Apart from SGWidget, there are also other things that most applications would need, such as file reading, file writing, and the use of colours.

Using SGEXTN to build apps feel like QWidget but without the signal-slot callbacks. Also, make sure to become familiar with function pointer syntax first before using SGEXTN, because SGEXTN callbacks are raw function pointers.

Instructions about how to set up SGEXTN are included below, first understand why SGEXTN exists.

#### QML?

QML is the Qt Quick way of writing declarative UI using JSON syntax and with use of JavaScript for functions. Qt intends this to be similar to frontend development in website building. However, if one just want to write C++ and see widgets on screen, that would not work. Also, writing even tiny functions in JavaScript means dealing with all of JavaScript's nonsense, such as literally no types. By using SGEXTN's SGWidget system, you would not need a single line of QML when building UI.

#### signal-slot?

Signal-slot is Qt's system for building callback functions. In Qt 6, they are essentially function pointers, which is good. However, using them requires the Q_OBJECT macro and MetaObject Compiler (MOC) processing, which increases compile time. SGEXTN abstracts that away by using raw function pointers for callbacks attached to timers (SGXTimer) and interactive UI elements including buttons (SGWButton subclasses) and input fields (SGWInput subclasses).

#### What if I want Qt stuff?

SGEXTN abstracts Qt stuff without disabling them. So if you really want to use Qt stuff, you can do that normally.

### Documentation

The SGEXTN Documentation site can be viewed [here](https://infinityintegral.github.io) on my GitHub Pages. On the documentation site, you can find more information related to various public API that SGEXTN offers. The site is made to resemble the layout of the Qt Documentation as much as possible.

### Demo app

The demo app for SGEXTN has not been built yet.

### Setting up SGEXTN

SGEXTN uses Qt Quick extensively and can only be used in a Qt project. Qt version 6.9 and above is recommended.

To use SGEXTN, copy the entire SGEXTN folder into the root folder of your project which should contain your project file (.pro). To include it, write the line
```qmake
include(SGEXTN/SGEXTN.pri)
```
at the top of your project file (.pro). After that, go to the file SGEXTN/userDefinedClasses/sgucentralmanagement.cpp, read through the comments in the file and customise whatever is needed. Do not change anything not specified in the SGEXTN folder.

Your custom code should be outside the SGEXTN folder. Classes in your custom code should have the prefix SGC if you are not planning for it to be reusable or SG followed by your app name if you want it to be reusable (in which case it should be in its own folder). The first word in the names of renderer classes should be "Render".

### Extending SGEXTN

You can extend SGEXTN by adding renderers. Renderers can be used to display shader output, non rectangular UI, and large amounts of UI.

To build a renderer, you need the following
- a vertex shader (.vert) in GLSL, built using QSB into a Qt Shader Binary (.qsb) for deployment across all rendering backends
- a fragment shader (.frag) in GLSL, built using QSB into a Qt Shader Binary (.qsb) for deployment across all rendering backends.
- a QML file (.qml) describing the QML Component
- C++ header (.h) and source (.cpp) files for the material
- C++ header (.h) and source (.cpp) files for the shader, the shader must upload uniform data
- C++ header (.h) and source (.cpp) files for the QQuickItem, this must set up the QQuickItem appropriately for rendering by Qt Quick
- C++ header (.h) and source (.cpp) files for the SGWidget, this must inherit SGWCustomRenderer and set up the SGWidget appropriately
- the type must be registered with the QML system, see comments on top of the dedicated function in SGEXTN/userDefinedClasses/sgucentralmanagement.cpp for more information

Refer to the SGEXTN/colourpickerrendering/huechoice folder for an example.

### File prefixes

SGEXTN uses file prefixes to mean different things.

- SGX: SGEXTN classes not using SGWidget in any way
- SGW: SGEXTN classes using SGWidget and the SGWidget module itself
- SGU: customisable part of SGEXTN, can be changed by user
- SGC: user's custom code

Names of all renderer classes should start with the word "Render".

## Completed Features
Note that this only includes public API available in SGEXTN version 5.1.0.
- additional primitives
	- SGXColourRGBA
	- SGXColourHSLA
	- SGXIdentifier
	- SGXTimeStamp
	- SGXVector2
	- SGXTouchEvent
- SGWidget GUI toolkit
	- SGWWidget
		- SGWBlankWidget
		- SGWBackground
			- SGWPageBackground
			- SGWScrollView
			- SGWSequentialScrollView
		- SGWLabel
			- SGWTextLabel
			- SGWIconLabel
			- SGWLongLabel
			- SGWSequentialLongLabel
		- SGWButton
			- SGWTextButton
			- SGWIconButton
		- SGWInput
			- SGWTextInput
			- SGWLongInput
		- SGWTouchReceiver
		- SGWCustomRenderer
		- SGWColourPickerWidget
	- SGWType
	- SGWHorizontalAlignment
	- SGWVerticalAlignment
	- SGWDefaultFonts
- file system interaction
	- SGXFile
	- SGXFileSystem
	- SGXFileBinUtilities
	- SGXFileZip
	- SGXFileDownloader
	- SGXFileUploader
- other userful stuff
	- SGWNotify
	- SGXTimer
	- SGXSingCorrectCore
	- SGXResizer
	- SGXThemeColours
- builtin customisation pages
	- SGWThemeCustomisationPage
	- SGWVesicleCustomisationPage
	- SGWSingCorrectCustomisationPage
- implement functions in here as needed
	- SGUCentralManagement

## Credits
- Qt (https://www.qt.io/)
- Git (https://git-scm.com/)
- GitHub (https://github.com/)
- LGPL License (https://opensource.org/license/lgpl-3-0)
- 05524F.sg SGEXTN (https://github.com/InfinityIntegral/SGEXTN) (ownself cite ownself)

## Contributing
The best way to contribute is to complain. To complain refers to informing me of a bug or suggesting a new feature to be included to the software. Pls refer to the "Contact me" section below.

If I perceive your suggested feature to be beyond the scope of the software, I will not approve it. However, you can still download the code and build your own feature. As long as you keep the .sg (or "SG" in this case) in your project name, I am ok with it.

## Contact me
Choose one of the following
- email to infinityintegral333@gmail.com
- message @05524F.sg on Instagram

## Am I blur
No.
