# SGEXTN ("SG" Extension for C++ and Qt)

## About this project
This project is WORK IN PROGRESS and should not be used for software development. More information will be provided upon completion of SGEXTN v5.

SGEXTN is designed to be a framework + app template built on top of Qt to simplify development of GUI apps.

versions list:  
SGEXTN v1: primitives and rendering based on QWidget (great architecture, but slow because QWidget does not use GPU)  
SGEXTN v2: added dynamic widget creation based on Qt Quick, file system, basic customisation (less powerful due to loss of classes, QML lookup overhead)  
SGEXTN v3: added colour picker (same issues as v2)  
SGEXTN v4: added SingCorrect module (same issues as v2)  
SGEXTN v5 (planned): same architecture as v1 but uses Qt Quick (supposed to be suitable for development use)

## Completed Features (available in v4)
- [x] C++ primitives extensions
	- [x] SGXColourRGBA (RGBA representation of a colour with 8 bits per channel, wraps unsigned int)
	- [x] SGXColourHSLA (HSLA representation of a colour with 8 bits per channel, contains 4 floats)
	- [x] SGXIdentifier (GUID with automatic registering, wraps QUuid)
	- [x] SGXVector2 (a struct of 2 SGXFloats for 2D vectors)
	- [x] SGXTimeStamp (a signed long long representing number of seconds since 19650809 123000)
	- [x] SGXTouchEvent (representation of touch input from the user)
- [x] Qt Quick components
	- [x] SGXQuickResizer (manages resizing of app UI based on window size)
	- [x] SGXThemeColourSetting (manages theme colours of the app)
	- [x] SGXQuickUIInterface (contains methods to create and add components)
		- [x] root widget of application
		- [x] parent widget of application, where everything is rendered
		- [x] non interactive widget displaying a solid colour
		- [x] non interactive single line text label, cuts off text if length is exceeded
		- [x] center aligned text label
		- [x] right aligned text label
		- [x] non interactive scrollable multi line text label, allows scrolling if height is exceeded
		- [x] non interactive icon
		- [x] button with text
		- [x] button with icon
		- [x] single line input field, automatically scrolls horizontally if length exceeded
		- [x] multi line input field, scrolls vertically if height exceeded
		- [x] scroll view
		- [x] touch receiver
		- [x] colour picker
		- [x] cute vesicles
- [x] file system usage
     - [x] SGXFileReader (struct allowing reading of all SGEXTN and C++ primitives from files with index seeking)
	- [x] SGXFileWriter (struct allowing writing of all SGEXTN and C++ primitives to files with overwriting by index)
	- [x] SGXFileSystem (non instantiatable struct with static methods for file system operations)
	- [x] SGXFileBinUtilities (non instantiable struct with static methods for usage of the recycling bin)
	- [x] SGXFileUploader (non instantiable struct with static methods for bringing in external files
	- [x] SGXFileDownloader (non instantiable struct with static methods for saving application files externally)
	- [x] SGXFileZipUtilities (non instantiable struct with static methods for creating and using zip files)
- [x] builtin customisation
- [x] working application template

## planned for SGEXTN v5
- [ ] class based GUI set with structure closely mirroring SGEXTN v1
	- [ ] SGWWidget
		- [x] SGWRoot
		- [x] SGWParent
		- [x] SGWStatusBar
		- [x] SGWBackground
			- [x] SGWBlankWidget
			- [x] SGWScrollView
		- [ ] SGWLabel
			- [ ] SGWTextLabel
			- [ ] SGWIconLabel
			- [ ] SGWLongLabel
		- [ ] SGWButton
			- [ ] SGWTextButton
			- [ ] SGWIconButton
		- [ ] SGWInput
			- [ ] SGWTextInput
			- [ ] SGWLongInput
		- [ ] SGWColourPicker
		- [ ] SGWGraphicsRenderer
		- [ ] SGWTouchReceiver
	- [ ] SGWFileDialog
		- [ ] SGWFileUpload
		- [ ] SGWFileDownload
- [ ] reimplemented vesicle customisation page
- [ ] reimplemented colour picker
- [ ] improved theme customisation page
- [ ] improved SingCorrect configs page
- [ ] SGXTimer (wrapper around QTimer to eliminate need for signal-slot, with single use version)

SGEXTN v5 will cover all functionalities in previous versions, so there would be no reason to use v1 because of missing stuff. 

SGEXTN v5 would also completely hide any trace of QML usage, so you will not have to use QObject::setProperty yourself or listen to QQuickItem::opacityChanged to get colour picker output.

By design, SGEXTN v5 will be weaker than raw Qt significantly in terms of customisation. However, greater control is provided compared to any previous version.

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
