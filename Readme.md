
## Crystal Color Center
The program allows managing file and directory patterns (e.g. extension or name matches) for:  
- [Double Commander](http://doublecmd.sourceforge.net/) (in Options - Colors - File types)
- Total Commander (in Configuration - Display - Color - Define colors by file type).
Since editing many patterns in those is way too slow.  

To download go to [Releases](https://github.com/cryham/ccc/releases).
Press Ctrl-F1 in program to see Help screen.  

Currently you can:
- Save and load program's own project xml file(s)
- Import from and export back into:
  * Double Commander's file: doublecmd.xml
  * Total Commander's file: color.ini
  * Import with merge into current list
- Manage the list
  * edit, add, remove patterns
  * adjust row color with R,G,B sliders
  * rearrange, move patterns and rows
  * toggle directory, hidden or group for pattern
  * use group sets to toggle visibility
- Utility
  * find pattern names, with occurences mark
  * change font size, spacing and other settings
  
TODO (not important):
  * multi select, move, edit
  * HSV sliders

## About
This utility program is written in C++17, using [SFML](https://github.com/SFML/SFML) for graphics,
GUI with [ImGui](https://github.com/ocornut/imgui) and [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml).

In sources there already are: [TinyXML2](https://github.com/leethomason/tinyxml2), ImGui with ImGui-SFML and [Native File Dialog](https://github.com/mlabbe/nativefiledialog).  

## Building

### General
Is done using [CMake](https://cmake.org/). I'm using Qt Creator IDE, which supports it.  

Tested on Debian 10 and Windows 7 with SFML 2.5.1.

### GNU/Linux

On **GNU/Linux** you'll need to get SFML installed.  
Command for Ubuntu (and Debian-based):  
`sudo apt-get install libsfml-dev`  
and also tools (if not present yet):  
`sudo apt-get install build-essential cmake git`  

To get sources, build and start in console use:
```
git clone https://github.com/cryham/ccc.git
cd ccc
mkdir build && cd build
cmake ..
make -j8
./ccc
```
Argument `-j8` means to use 8 threads. If needed you can update your git clone to latest version with `git pull` after.

### Windows

On **Windows** you need to download unpack install SFML [from here](https://www.sfml-dev.org/download.php).
Latest version and matching your VS (likely 2017 64-bit).  
Then SFML needs the environment variable SFML_ROOT set to path where SFML is.  
Alternatively (if problems occur building CCC) the harder ways is to get and build SFML from sources.  

## Screenshot

![](https://raw.githubusercontent.com/cryham/ccc/master/screenshot.png)
