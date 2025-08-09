# SGEXTN ("SG" Extension for C++ and Qt)

## About this project
This project is WORK IN PROGRESS and should not be used for software development. More information will be provided upon completion of SGEXTN v5.

SGEXTN is designed to be a framework + app template built on top of Qt to simplify development of GUI apps.

versions list:  
SGEXTN v1.0.0: primitives and rendering based on QWidget (great architecture, but slow because QWidget does not use GPU)  
SGEXTN v2.0.0: added dynamic widget creation based on Qt Quick, file system, basic customisation (less powerful due to loss of classes, QML lookup overhead)  
SGEXTN v3.0.0: added colour picker (same issues as v2.0.0)  
SGEXTN v4.0.0: added SingCorrect module (same issues as v2.0.0)  
SGEXTN v5.0.0 (planned): same architecture as v1 but uses Qt Quick (supposed to be suitable for development use)

## Completed Features (available in v4.0.0)
- [x] C++ primitives extensions
	- [x] SGXColourRGBA
	- [x] SGXColourHSLA
	- [x] SGXIdentifier
	- [x] SGXVector2
	- [x] SGXTimeStamp
	- [x] SGXTouchEvent
- [x] Qt Quick components
	- [x] SGXQuickResizer
	- [x] SGXThemeColourSetting
	- [x] SGXQuickUIInterface
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
     - [x] SGXFileReader
	- [x] SGXFileWriter
	- [x] SGXFileSystem
	- [x] SGXFileBinUtilities
	- [x] SGXFileUploader
	- [x] SGXFileDownloader
	- [x] SGXFileZipUtilities
- [x] builtin customisation
- [x] working application template

## planned for SGEXTN v5.0.0
- [ ] class based GUI set with structure closely mirroring SGEXTN v1
	- [ ] SGWWidget
		- [x] SGWRoot
		- [x] SGWParent
		- [x] SGWStatusBar
		- [x] SGWBlankWidget
		- [x] SGWBackground
			- [x] SGWPageBackground
			- [x] SGWScrollView
		- [x] SGWLabel
			- [x] SGWTextLabel
			- [x] SGWIconLabel
			- [x] SGWLongLabel
		- [x] SGWButton
			- [x] SGWTextButton
			- [x] SGWIconButton
		- [x] SGWInput
			- [x] SGWTextInput
			- [x] SGWLongInput
		- [x] SGWTouchReceiver
		- [x] SGWCustomRenderer
		- [x] SGWColourPicker
- [ ] reimplement vesicle customisation page
- [ ] reimplement colour picker
- [ ] improve theme customisation page
- [ ] improve SingCorrect configs page
- [ ] SGXTimer (wrapper around QTimer to eliminate need for signal-slot, with single use version)
- [ ] pull down notification (input invalid)
- [ ] make notification separate widget

SGEXTN v5.0.0 will cover all functionalities in previous versions, so there would be no reason to use v1 because of missing stuff. 

SGEXTN v5.0.0 would also completely hide any trace of QML usage, so you will not have to use QObject::setProperty yourself or listen to QQuickItem::opacityChanged to get colour picker output.

By design, SGEXTN v5.0.0 will be weaker than raw Qt significantly in terms of customisation. However, greater control is provided compared to any previous version.

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
