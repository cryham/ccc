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
	sf::Uint32 c;
	bool dir, link;
	Pat()
		:dir(false), link(false), c(0)
	{   }
};

//  Color, for patterns
//------------------------------------------------
struct Clr
{
	sf::Uint32 c;
//	sf::Color clr;
	Clr()
		:c(0)
	{	}
	bool operator<(const Clr& o) const
	{	return c < o.c;  }
};

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
	bool LoadFromDC(std::string file);  // DC doublecmd.xml
	bool SaveToDC(std::string file);

	bool ImportFromTC(std::string file);  // TC color.ini

	//  project file, own
	bool Load(std::string file);
	bool Save(std::string file);

};
