# STABAX ENGINE #

## Contributors ##
+ Stabax Corp.
+ Maxime 'stalker2106' Martens

## About ##
StbxEngine is a basic, hassle-free, feature-full implementation of a modern C++ Game Engine.
It provides a SFML-Powered 2D context (extendable to 3D with openGL) with pre-built modules.

This projects aims to give developers a way to program video games with basic C++ Knowledge;
No more time-wasting tasks, start writing the game code right away!

## Build Status ##

You can check build status for latest version [at this address](http://stabax.org/stbxengine/)

## Documentation ##

This library is documented online [at this address](http://stabax.org/stbxengine/doc/)

## License ##

This library is released under MIT License
Copyright 2017 Stabax Ltd.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Dependencies ##
+ SFML for Graphics and Window
  * Optionally OpenGL for rendering 3D context
+ Texu's GUI for rendering interfaces
+ PugiXML for XML Parsing
+ Nlohmann's Json for Json Parsing


### Getting started ###

Check out our [latest guide here](http://stabax.org/stbxengine/doc/md_doc_GettingStarted.html)

## Build the library! ##

### Command Line (Make/GCC/Clang)

The engine project uses CMake. therefore, make sure you have it installed on target machine.
You can then run cmake generation for your desired environemment:

    #!/bin/bash

    cmake ./build/

### Visual Studio (2015)

Navigate to @REPO/vs/ folder, open StbxEngine.sln solution to build it using Visual Studio.

## Compile with engine ##

### Command Line (Make/GCC/Clang)

You can directly link with StbxEngine by adding "-lsengine" to your linker command line.

### Visual Studio (2015)

Add library binary previously built (sengine.lib) to your linker settings.