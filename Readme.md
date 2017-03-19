
## Crystal Color Center
The program allows managing file and directory patterns (e.g. extension or name matches)  
for [Double Commander](http://doublecmd.sourceforge.net/) (in Options - Colors - File types).  
Since editing many patterns there is way too slow.  

Currently you can:
- Save and load the program's own project xml file
- Import from Double Commander's file: doublecmd.xml.
- Export into doublecmd.xml
- Manage the list
  * edit, add, remove patterns
  * adjust color with R,G,B sliders
  * search pattern names
  * rearrange: move patterns and rows
  * edit pattern and row color

TODO (less important):
- Import and export Total Commander's file: color.ini.
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
