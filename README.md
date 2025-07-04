# SGEXTN ("SG" Extension for C++, Qt, and OpenGL)

## About this project...
This project has not been completed.

This is a template application to make building applications in Qt easier. It internally uses Qt Quick but SGEXTN functions are designed for imperative UI, similar to QWidget and different from Qt Quick's declarative UI. There is also a wide variety of primitive structs that allow you to group, store, and use data more easily in addition to file system usage methods.

"SG" refers to Singapore, my home country. It does not reference the Qt Quick scene graph. SGEXTN is designed to let you not worry about the scene graph and instead use it like a customised, GPU-accelerated version of QWidget.

For OpenGL support, you should subclass QQuickItem and use QSGGeometryNode for rendering. Since rendering is a highly customised process, SGEXTN does not simplify it and you are expected to use the Qt Quick API without any SGEXTN layer over it. SGEXTN does not modify scene graph internals (again, "SG" is Singapore, my home country, not the short form for scene graph) and is fully compatible with custom rendering. You may look at the cutevesicles folder for syntax.

Documentation is included in the form of comments in header files.

SGEXTN v1 uses QWidget, it is fully functional. I switched the rendering method because Qt Quick is newer, faster, and more compatible with mobile platforms. Although the current version uses Qt Quick internally, the SGEXTN wrapper layer allows you to use it as if it is QWidgets.

File name prefixes:  
SGX - SGEXTN files, do not touch those unless you know very well what you are doing  
SGXRender - SGEXTN files used in rendering of builtin cute vesicles, these are useful to look at to learn the structure of custom rendering  
SGU - kind of SGEXTN files, you can edit the values of properties inside if the comments inside explicitly allows you to. Keep a copy of the original so you can revert the file if something internal breaks  
SGC - I cannot enforce this, but you are supposed to start your custom classes with this prefix  
SGCRender - I cannot enforce this, but you are strongly encouraged to start custom classes related to custom rendering with this

## Included in latest release...
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
		- [x] non interactive scrollable multi line text label, allows scrolling if height is exceeded
		- [x] non interactive icon
		- [x] button with text
		- [x] button with icon
		- [x] single line input field, automatically scrolls horizontally if length exceeded
		- [x] multi line input field, scrolls vertically if height exceeded
		- [x] scroll view
		- [x] touch receiver
		- [x] cute vesicles
- [x] file system usage
     - [x] SGXFileReader (struct allowing reading of all SGEXTN and C++ primitives from files with index seeking)
	- [x] SGXFileWriter (struct allowing writing of all SGEXTN and C++ primitives to files with overwriting by index)
	- [x] SGXFileSystem (non instantiatable struct with static methods for file system operations)
	- [x] SGXFileBinUtilities (non instantiable struct with static methods for usage of the recycling bin)
	- [x] SGXFileUploader (non instantiable struct with static methods for bringing in external files
	- [x] SGXFileDownloader (non instantiable struct with static methods for saving application files externally)
	- [x] SGXFileZipUtilities (non instantiable struct with static methods for creating and using zip files)
- [x] customisable theme colours
- [x] customisable vesicle properties
- [x] working application template

## Work in progress...
- [ ] colour picker
- [ ] specialised input fields
- [ ] hidden theme colours settings page

## Credits...
- Qt (https://www.qt.io/)
- Git (https://git-scm.com/)
- GitHub (https://github.com/)
- LGPL License (https://opensource.org/license/lgpl-3-0)
- 05524F.sg SGEXTN (https://github.com/InfinityIntegral/SGEXTN) (ownself cite ownself)

## Contributing...
The best way to contribute is to complain. To complain refers to informing me of a bug or suggesting a new feature to be included to the software. Pls refer to the "Contact me" section below.

If I perceive your suggested feature to be beyond the scope of the software, I will not approve it. However, you can still download the code and build your own feature. As long as you keep the .sg (or "SG" in this case) in your project name, I am ok with it.

## Contact me...
Choose one of the following
- email to infinityintegral333@gmail.com
- message @05524F.sg on Instagram

## Am I blur...
No.
