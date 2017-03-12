#pragma once
#include <vector>
#include <string>
#include <set>
#include <SFML/Config.hpp>
typedef sf::Uint8 byte;


//  Color, for patterns
//------------------------------------------------
struct SClr
{
	byte r,g,b;  // color

	SClr()
		:r(255),g(255),b(255)
	{	}
	SClr(byte rr, byte gg, byte bb)
		:r(rr),g(gg),b(bb)
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

	bool dir, lnk, exe;   // attributes
	std::string attr;
	char grp;  // group for sorting..

	//  visual only,  not saved, computed by Update()
	int x,y, xw, l;  // pos on screen, width, line

	Pat()
		:dir(false), lnk(false), exe(false)
		,grp(0)
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
	std::vector<int> lines;  // line offsets for patterns

	std::set<sf::Uint32> clr;  // colors, for count

	List();
	void Default();

	//  update view,  run after any changes in pat
	void Update(int xMin, int xMax, int xa, int ya);  // x,y, xw, l, ofs
	//  app  for text get width
	App* app = nullptr;
	void SetApp(App* p) {  app = p;  }

	//  load, import
	bool LoadDC(const char* file);  // from DC doublecmd.xml
	bool SaveDC(const char* file);

	bool ImportTC(std::string file);  // TC color.ini

	//  project file, own
	bool Load(const char* file);
	bool Save(const char* file);
};
