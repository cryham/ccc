[![Build Status](https://travis-ci.org/cryham/ccc.svg?branch=master)](https://travis-ci.org/cryham/ccc)

# Crystal Color Center
The program's allows managing file and directory patterns (e.g. extension or name matches)  
for Double Commander (in Options - Colors - File types).  
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
This small utility program is written in C++ and using SFML for graphics.

## Compiling
Using CMake, it should be possible to build easily. I'm using Qt Creator.  

On Linux you'll need to get SFML installed (e.g. libsfml-dev on Debian like).

On Windows SFML needs the environment variable SFML_ROOT to be defined.  
After this the program should build.  

In sources there already are TinyXML2 files.  
