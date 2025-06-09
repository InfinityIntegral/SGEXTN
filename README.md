# SGEXTN ("SG" Extension for C++, Qt, and OpenGL)

## About this project...
This project was never supposed to exist... ok, it did exist, but just as a basic template app that I put on GitHub and just essentially wont touch again...

But I was building an app and had weird behaviour in the UI... Then I realised that I have been using QWidget style sheets wrongly the whole time, they are called **cascading** style sheets for a reason...

Obviously, I would rather have each button maintain its own style and be a separate object, instead of having global stylesheets being kaypoh all the time, and also I would rather have real properties in C++ then trying to parse a particularly blur JSON-ish variant called "CSS". Additionally, colours are uints, not random strings, that by the time it is parsed to change a widget colour, an old auntie could have walked from Tuas to Changi and back...

And that is incompatible with QWidget drawing, so I have to redo QWidget drawing...

But since I am rebuilding so much stuff, why not just wrap everything in my custom wrapper to make programming easier in future?

Thus this project: SGEXTN

## Built with...
- Qt (C++ GUI framework)
- OpenGL (through Qt, for rendering)

## Prerequisites
You must have Qt installed on your computer with necessary build tools.

## Installation
You download the source code.

## Using the software...
Download the source code and open it in Qt and start coding your project, I hope I will have time to write documentation.

## What to expect...
Even I do not know

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
