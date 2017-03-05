#pragma once
#include <vector>
#include <string>
#include <set>
#include <SFML/Config.hpp>


//  Pattern match, for e.g. extension or name
//------------------------------------------------
struct Pat
{
	std::string s;  // eg. *.cpp
	sf::Uint8 r,g,b;  // color

	bool dir, link;   // attributes
	std::string attr;

	Pat()
		:dir(false), link(false)
		,r(255),g(255),b(255)
	{   }

	void SetClr(sf::Uint32 c);
	sf::Uint32 GetClr();
};

//  Color, for patterns
//------------------------------------------------
/*struct Clr
{
	sf::Uint32 c;
//	sf::Color clr;

	Clr()
		:c(0)
	{	}

	bool operator<(const Clr& o) const
	{	return c < o.c;  }
};/**/


//  List of both
//------------------------------------------------
class List
{
public:
	std::vector<Pat> pat;  // patterns
	std::set<sf::Uint32> clr;  // colors
//	std::map<Pat, Clr> pt2clr;
	List();
	void Default();

	//  load, import
	bool LoadDC(std::string file);  // from DC doublecmd.xml
	bool SaveDC(std::string file);

	bool ImportTC(std::string file);  // TC color.ini

	//  project file, own
	bool Load(std::string file);
	bool Save(std::string file);
};
