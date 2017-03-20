
## Crystal Color Center
The program allows managing file and directory patterns (e.g. extension or name matches)  
for [Double Commander](http://doublecmd.sourceforge.net/) (in Options - Colors - File types),  
and also for Total Commander (in Configuration - Display - Color - Define colors by file type).  
Since editing many patterns there is way too slow.  

Press Ctrl-F1 in program to see Help screen.  

Currently you can:
- Save and load the program's own project xml file
- Import from and export back into:
  * Double Commander's file: doublecmd.xml
  * Total Commander's file: color.ini
- Manage the list
  * edit, add, remove patterns
  * adjust row color with R,G,B sliders
  * rearrange, move patterns and rows
  * search pattern names
  
TODO (less important):
- Import with merge into current list
- Manage
  * dir, link, exe checkboxes, updating attributes string
  * hsv sliders
  * group by id, sorting
  * multi select, move, edit
  * rating groups

## General
This utility program is written in C++, using [SFML](https://github.com/SFML/SFML) for graphics,
GUI with [ImGui](https://github.com/ocornut/imgui) and [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml).

## Compiling
Using [CMake](https://cmake.org/), it should be possible to build easily.  
I'm using Qt Creator IDE, which supports it.  

On GNU/Linux you'll need to get SFML installed. At least version 2.2.  
E.g. for Ubuntu (and Debian-based):  
`sudo apt-get install libsfml-dev`  

On Windows SFML needs the environment variable SFML_ROOT to be defined.  
After this the program should build.  

In sources there already are: TinyXML2, ImGui and ImGui-SFML.  
