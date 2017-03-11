
## Crystal Color Center
The program allows managing file and directory patterns (e.g. extension or name matches)  
for [Double Commander](http://doublecmd.sourceforge.net/) (in Options - Colors - File types).  
Since editing many patterns there is way too slow.  

Currently you can:
- Import from Double Commander's file: doublecmd.xml.
- Save and load the program's own project xml file
- Export result to doublecmd.xml

TODO (In future it will allow to):
- import from Total Commander's file: color.ini.
- export results to colors.ini.
- import with merge into current set

- managing the list of patterns and colors
  * edit, add, remove
  * adjust color rgb, hsv sliders
  * rearrange (move), split, merge
  * group by id
  * sort by name, color
  * multi select / group color adjust
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
