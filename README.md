# STABAX ENGINE #

## Contributors ##
+ Stabax Corp.
+ Maxime 'stalker2106' Martens

## About ##
StbxEngine is a basic implementation of Game Engine; with a modular pattern. It provides a 2D context (extendable to 3D with openGL) with pre-built modules such as Developer console, XML Menu component, HUD with custom panels, wether draggables or static, and many more !

This projects aims to give developers a way to program video games with basic C++ Knowledge

## Build Status ##

You can check build status for latest version [at this address](http://vault.maximemartens.fr/stbxengine/)

## Documentation ##

This library is documented online [at this address](http://vault.maximemartens.fr/stbxengine/doc/)

## License ##

This library is released under MIT License
Copyright 2017 Stabax Ltd.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Dependencies ##
+ PugiXML for XML Parsing
+ SFML for Graphics and Window
  * Optionally OpenGL for rendering 3D context

### Getting started ###

Check out our [latest guide here](http://vault.maximemartens.fr/stbxengine/doc/md_doc_GettingStarted.html)

### Get library

To begin writing your game, clone latest revision of engine: 
	#!bash
	
	git clone http://bitbucket.org/stalker2106/stbxengine.git

## Build it! ##

### Command Line (GCC/Clang)

build the library binary depending on your needs with command line:
	#!bash
	
	make static
OR
	make dynamic

### Visual Studio (2013)

Navigate to @REPO/vs/ folder, open StbxEngine.sln solution to build it using Visual Studio.

## Compile with engine ##

Add library binary previously built to your linker settings or add "-lsengine" to your linker command line