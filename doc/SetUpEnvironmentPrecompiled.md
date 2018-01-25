## Set up your environment (Using precompiled libs)

You can download the latest binary of the library on the Stabax website in the library section.\n
Follow [this link]() and select the desired version of library.\n

Upack the downloaded folder.\n
It should contain the following architecture:\n

    StbxEngine
    |- include
    |- lib
    |- doc

Only the lib and include folder are important there, because you are actually browsing the doc folder by reading this.\n
Put the path of these folders respectively in additional include directories and additional library directories (on VS/XCode)\n
or add the following arguments to your compiler command line:\n

    -I"path/to/include" -L"path/to/lib" -lsengine 

All done, you can build your first StbxEngine project to see your first window pop-out !