#pragma once
#include <vector>
#include <string>
#include <set>
#include <SFML/Config.hpp>


//  Color, for patterns
//------------------------------------------------
struct SClr
{
	sf::Uint8 r,g,b;  // color

	SClr() : r(255),g(255),b(255)
	{	}

	void Set(sf::Uint32 u);
	sf::Uint32 Get();

	bool operator!=(const SClr& c) const
	{
		return r != c.r || g != c.g || b != c.b;
	}
};


//  Pattern match, for e.g. extension or name
//------------------------------------------------
struct Pat
{
	std::string s;  // eg. *.cpp
	SClr c;

	bool dir, link;   // attributes
	std::string attr;

	int x,y, xw, l;  // pos on screen, width, line

	Pat()
		:dir(false), link(false)
		,x(0),y(0), xw(0), l(0)
	{   }
};


//  List of both
//------------------------------------------------
class App;
class List
{
public:
	std::vector<Pat> pat;  // patterns
	std::set<sf::Uint32> clr;  // colors
//	std::map<Pat, Clr> pt2clr;

	List();
	void Default();

	//  run after any changes in pat
	void Update(int xMax, int xa, int ya);  // x,y, xw, l
	App* app;  // for text get width
	void SetApp(App* p) {  app = p;  }

	//  load, import
	bool LoadDC(std::string file);  // from DC doublecmd.xml
	bool SaveDC(std::string file);

	bool ImportTC(std::string file);  // TC color.ini

	//  project file, own
	bool Load(std::string file);
	bool Save(std::string file);
};
