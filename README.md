# SGEXTN ("SG" Extension for C++, Qt, and OpenGL)

## About this project...
This project was never supposed to exist... ok, it did exist, but just as a basic template app that I put on GitHub and just essentially wont touch again...

But I was building an app and had weird behaviour in the UI... Then I realised that I have been using QWidget style sheets wrongly the whole time, they are called **cascading** style sheets for a reason...

Obviously, I would rather have each button maintain its own style and be a separate object, instead of having global stylesheets being kaypoh all the time, and also I would rather have real properties in C++ then trying to parse a particularly blur JSON-ish variant called "CSS". Additionally, colours are unsigned ints, not random strings, that by the time it is parsed to change a widget colour, an old auntie could have walked from Tuas to Changi and back...

And that is incompatible with QWidget drawing, so I have to redo QWidget drawing...

But since I am rebuilding so much stuff, why not just wrap everything in my custom wrapper to make programming easier in future?

Thus this project: SGEXTN

Note that "SGX" is short for "SGEXTN", the project name, and is used as a prefix for all classes and structs. It does not reference anything else.

## Built with...
- Qt (C++ GUI framework)
- OpenGL (through Qt, for rendering)

## Prerequisites
You must have Qt installed on your computer with necessary build tools.

## Installation
You download the source code.

## Using the software...
Download the source code and open it in Qt and start coding your project. The documentation is comments in header files, I made them as clear as possible.

## What to expect...
- [ ] C++ primitives extensions
	- [x] SGXColourRGBA (RGBA representation of a colour with 8 bits per channel, wraps unsigned int)
	- [x] SGXColourHSLA (HSLA representation of a colour with 8 bits per channel, contains 4 floats)
	- [x] SGXIdentifier (GUID with automatic registering, wraps QUuid)
	- [ ] SGXVector2 (a struct of 2 SGXFloats for 2D vectors)
	- [ ] SGXTimeStamp (a long long representing time since 19650809 120000)
- [ ] Qt GUI classes with custom drawing and resizing
     - [ ] SGXRootWindow (root widget of the application, does nothing, inherits QWidget)
     - [ ] SGXWidget (a widget with solid colour that does nothing, inherits QWidget)
	- [ ] SGXText (a widget that displays text in SingScript, inherits QLabel)
	- [ ] SGXIcon (a widget that displays text in a special icon font, inherits QLabel)
	- [ ] SGXTextButton (a button with text display in SingScript, inherits QPushButton)
	- [ ] SGXIconButton (a button that displays text in a special icon font, inherits QPushButton)
	- [ ] SGXIntInputField (a input field taking a integer, inherits QLineEdit)
	- [ ] SGXFloatInputField (a input field taking a floating point number, inherits QLineEdit)
	- [ ] SGXTextInputField (a multiline input field, inherits QTextEdit)
	- [ ] SGXLayout (a widget that has custom scripting to manage the layout of other widgets, inherits QWidget)
	- [ ] SGTouchReceiver (a nondisplaying widget that accepts touch events, inherits QWidget)
- [ ] OpenGL simplifications
     - [ ] SGXShaderDisplay (a widget that draws by OpenGL and contains a shader programme as a property, inherits QOpenGLWidget)
     - [ ] SGXShaderDataGroup (a struct containing a vao, a vbo, and a ebo, all in a group for 2D rendering, also contains methods for drawing and keeps tracks of buffer sizes)
	- [ ] SGXTransformFeedbackGroup (a struct containing a shader programme and 2 buffers for transform feedback)
	- [ ] SGXShaderGlobalVariable (a struct containing data to set shader uniforms)
- [ ] file system usage
     - [ ] SGXFileReader (struct allowing reading of all SGEXTN primitives from files with index seeking)
	- [ ] SGXFileWriter (struct allowing writing of all SGEXTN primitives to files with overwriting by index)
	- [ ] SGXFileSystemManagement (non instantiatable struct with static methods for file system operations)
	- [ ] SGXCannotLah (logging error messages in a file ".cannotlah")
- [ ] working application template

potential future extensions include networking stuff and PDF stuff and 3D rendering stuff and bluetooth stuff and more cross platform stuff

## Contributing...
The best way to contribute is to complain. To complain refers to informing me of a bug or suggesting a new feature to be included to the software. Pls refer to the "Contact me" section below.

If I perceive your suggested feature to be beyond the scope of the software, I will not approve it. However, you can still download the code and build your own feature. As long as you keep the .sg in your project name, I am ok with it.

## Who contributed the most...
student 05524F (InfinityIntegral)

(that is me)

(the index number comes from my index number in the Primary School Leaving Examinations 2021)

## License info...
This software is distributed under the MIT License. For more information, pls see LICENSE.txt

## Contact me...
Choose one of the following
- email to infinityintegral333@gmail.com
- message @05524F.sg on Instagram

## Made possible by...
- the README format is inspired by Best-README-Template, which can be found at https://github.com/othneildrew/Best-README-Template
- the application is built using Qt, their official website is https://qt.io
- OpenGL is used for rendering, their official website is https://opengl.org
- the license terms of the MIT license are copied from the website of the Open Source Initiative which can be accessed at https://opensource.org
- the version control used is Git, their official website is https://git-scm.com
- the backup method used is GitHub, their official website is https://github.com
- All 05524F software is powered by Singapore, this refers to that student 05524F (InfinityIntegral) learnt programming, mathematics, logic, and self-study skills in Singapore.

## Am I blur...
No.
