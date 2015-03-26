# Introduction #

This is a basic guide on compiling DViz using Qt 4.5.3 on Windows XP Pro.

# Building DViz #

  1. Download and install Qt from [http://qt.nokia.com/downloads](http://qt.nokia.com/downloads). The LGPL/free version is fine.
  1. Download and install TortoiseSVN from http://tortoisesvn.net/downloads - any SVN client will do, really.
  1. Check out the DViz source code - SVN repository URL is http://dviz.googlecode.com/svn/trunk/. See the [Source tab](http://code.google.com/p/dviz/source/checkout) (above) for more details.
  1. Open Qt Creator (Start Menu -> Qt -> Qt Creator )
  1. Use File->Open to open dviz.pro from wherever you stored the DViz source. dviz.pro is in the '/src/' folder in the dviz source tree.
  1. From the 'Build' menu in Qt Creator, choose 'Build All'
  1. Before you can run DViz, you'll need to copy the DLLs from /src/external/ffmpeg/lib to /src/debug (or /src/release, whichever Qt Creater built dviz.exe in)
  1. You'll also want to copy the 'songs.db' from the /src/songs.db location to the same folder as dviz.exe
  1. Now you can run DViz by using Qt Creator. Choose the Build menu again and click 'Run.'

# Running DViz outside Qt Creator #

  * To run DViz outside Qt Creator, you'll need to copy the relevant DLLs from c:\qt\...\qt\bin.
> > The '...' depends on the version of Qt you downloaded.
  * You'll need mingw10.dll, QtCore4.dll, QtGui4.dll, QtNetwork4.dll, QtOpenGL4.dll, QtScript4.dll, QtSql4.dll, QtSvg4.dll, QtXml4.dll, and QtXmlPatterns4.dll
  * Copy these DLLs to the same folder as dviz.exe.
  * You'll need the Qt plugins from the Qt install location (C:\qt\...\qt\plugins) inorder to use the song database or use JPEGs on windows.
  * Copy the entire Qt Plugins folder to the same folder as dviz.exe
  * With the addition of Exiv2 to the code base, you'll need the libexpat.dll and libexpatw.dll in the same folder as dviz.exe
  * Copy the expat dlls from the src/imgtool/exiv2-0.18.2-qtbuild/win32/expat201/Bin/ into the same folder as dviz.exe
  * Now you can run DViz by just double-clicking on dviz.exe

# Building the DViz Network Viewer #

DViz supports a network viewer for transmitting content over the network to be viewed on other computers. DViz only transmits the binary description of the items on the slide, not the actual rendered slide. It leaves the rendering of the slide up to the network viewer, allowing DViz to put some of the burden of rendering on the client.

To build and run the viewer, it is very similar to building dviz.exe. Just substitute viewer.pro for dviz.pro (above), and dviz-viewer.exe instead of dviz.exe. The viewer.pro is located in the /src/viewer subfolder, and the dviz-viewer.exe will be put in either /src/viewer/debug or /src/viewer/release. You'll have to copy the DLLs into the viewer's folder, just like you did above.

For information on using the network viewer, see [UsingDVizViewer](UsingDVizViewer.md).