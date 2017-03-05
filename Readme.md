# Crystal Color Center
The program's purpose is to manage my file and directory patterns (e.g. extension or name matches)  
for Double Commander (in Options - Colors - File types).

TODO (In future it will allow):
- importing from doublecmd.xml also for Total Commander's color.ini.
- exporting results to those DC and TC files
- saving and loading own project files
- managing the list of patterns and colors
- e.g. rearrange (move), split, merge, group, etc.

## General
This small utility program is written in C++ and using SFML for graphics.

## Compiling
Using CMake, it should be possible to build easily. I'm using Qt Creator.  
Since I'm using SFML, CMake needs the environment variable SFML_ROOT to be defined.  
After this the program should build.  
In sources there already are TinyXML2 files.  
