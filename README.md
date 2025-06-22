# SGEXTN ("SG" Extension for C++, Qt, and OpenGL)

## About this project...
This project has not been completed.

This is a template application to make building applications in Qt easier. It internally uses Qt Quick but SGEXTN functions are designed for a dynamic UI creation, QWidget style mindset. Shaders are supported through Qt only. There is also a wide variety of primitive structs that allow you to group, store, and use data more easily.

Documentation is included in the form of comments in header files.

SGEXTN v1 uses QWidget, it is fully functional (though without OpenGL support). I switched the rendering method because Qt Quick is newer, faster, and more compatible with mobile platforms.

Note that "SGX" is short for "SGEXTN", the project name, and is used as a prefix for all classes and structs. It does not reference anything else. "SGU" is short for "SGEXTN User Defined Class", these are classes that the programmer should write code in, unlike the SGX classes which the programmer should not touch. You are strongly recommended to began the name of application-specific classes with "SGC" for "SGEXTN-powered Application Custom Class".

## What to expect...
- [x] C++ primitives extensions
	- [x] SGXColourRGBA (RGBA representation of a colour with 8 bits per channel, wraps unsigned int)
	- [x] SGXColourHSLA (HSLA representation of a colour with 8 bits per channel, contains 4 floats)
	- [x] SGXIdentifier (GUID with automatic registering, wraps QUuid)
	- [x] SGXVector2 (a struct of 2 SGXFloats for 2D vectors)
	- [x] SGXTimeStamp (a signed long long representing number of seconds since 19650809 123000)
	- [x] SGXTouchEvent (representation of touch input from the user)
- [ ] Qt Quick components
	- [x] SGXQuickResizer (manages resizing of app UI based on window size)
	- [x] SGXThemeColourSetting (manages theme colours of the app)
	- [x] SGXQuickUIInterface (contains methods to create and add components)
		- [x] root widget of application
		- [x] parent widget of application, where everything is rendered
		- [x] non interactive widget displaying a solid colour
		- [ ] non interactive single line text label, cuts off text if length is exceeded
		- [ ] non interactive scrollable multi line text label, allows scrolling if height is exceeded
		- [ ] non interactive icon
		- [ ] button with text
		- [ ] button with icon
		- [ ] single line input field, automatically scrolls horizontally if length exceeded
		- [ ] multi line input field, scrolls vertically if height exceeded
		- [ ] scroll view
		- [ ] touch receiver
		- [ ] cute squishy vesicles
- [ ] file system usage
     - [ ] SGXFileReader (struct allowing reading of all SGEXTN and C++ primitives from files with index seeking)
	- [ ] SGXFileWriter (struct allowing writing of all SGEXTN and C++ primitives to files with overwriting by index)
	- [ ] SGXFileSystemManagement (non instantiatable struct with static methods for file system operations)
	- [ ] SGXCannotLah (logging error messages in a file "cannot.lah")
- [ ] working application template

potential future extensions include networking stuff and PDF stuff and 3D rendering stuff and bluetooth stuff and more cross platform stuff

## Contributing...
The best way to contribute is to complain. To complain refers to informing me of a bug or suggesting a new feature to be included to the software. Pls refer to the "Contact me" section below.

If I perceive your suggested feature to be beyond the scope of the software, I will not approve it. However, you can still download the code and build your own feature. As long as you keep the .sg in your project name, I am ok with it.

## Contact me...
Choose one of the following
- email to infinityintegral333@gmail.com
- message @05524F.sg on Instagram

## Am I blur...
No.
