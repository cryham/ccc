#pragma once
#include <vector>
#include <string>
#include <set>
#include <deque>
#include <SFML/Config.hpp>
typedef sf::Uint8 byte;


//  Color, for patterns
//------------------------------------------------
struct SClr
{
	byte r,g,b;  // color
	//float h,s,v;  //todo: use,save hsv

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
	std::string s;  // pattern eg. *.cpp
	SClr c;  // color

	std::string attr;  // DC syntax  -* files  d* dirs
	bool dir;
	bool onlyDC, onlyTC;  // special


	bool hide;   // hidden, if true won't be exported

	bool group;  // group start, s is group name, if hide then whole group hidden
	bool hideByGrp;  // hidden by group, set in Update

	int grpSet;  // group set id
	bool hideBySet;  // hidden by set, set in Update

	bool show;  // for gui list, set in Update
	bool Visible() const  // for export
	{	return !(hide || hideByGrp || hideBySet);  }


	//  visual only,  not saved, computed by Update()
	int x,y, xw, l;  // pos on screen, width, line

	bool match;  // find
	bool sel;  // selected todo

	Pat()
		:x(0),y(0), xw(0), l(0)
		,match(false), sel(false)
		,dir(false)
		,onlyDC(false), onlyTC(false)
		,hide(false), hideByGrp(false)
		,group(false), grpSet(0), hideBySet(false)
		,show(true)
	{   }

	void SetDir(bool d);
};


//  List of both
//------------------------------------------------
class App;
class List
{
public:
	//  vars
	std::deque<Pat> pat;  // patterns
	std::vector<int> lines;  // line offsets for patterns

	//  stats, set in Update
	struct Stats
	{
		std::set<sf::Uint32> clrs;  // unique colors, for count
		int groups = 0;
		int linesReal = 0;  // visible and not group
	} st;

	//  visibility sets
	const static int maxSets = 10;
	int curSets = 0;  // auto, max used group set, for checkboxes count
	bool visSet[maxSets];


	//  ctor
	List();
	void Clear();

	//  app  for text get width
	App* app = nullptr;
	void SetApp(App* p) {  app = p;  }


	//  view  ----
	int LineLen(int id);  // get line length, id of line

	//  update view,  run after any changes in pat
	void Update(int xMin, int xMax, int xa, int ya);  // x,y, xw, l, ofs


	//  import, export  ----
	bool ImportDC(const char* file);  // DC doublecmd.xml
	bool ExportDC(const char* file);

	bool ImportTC(const char* file);  // TC color.ini
	bool ExportTC(const char* file);

	//  project file, own xml
	bool Load(const char* file);
	bool Save(const char* file);
};
