#pragma once
#include <vector>
#include <string>


//  Pattern match, for e.g. extension or name
//------------------------------------------------
struct Pat
{
	std::string s;  // eg. *.cpp
	bool dir, link;
	Pat()
		:dir(false), link(false)
	{   }
};

//  Color, for pattern
//------------------------------------------------
struct Clr
{
	int c;
//	sf::Color clr;
	Clr()
		:c(0)
	{	}
};

//  List of both
//------------------------------------------------
class List
{
public:
	std::vector<Pat> pat;  // patterns
	std::vector<Clr> clr;  // colors
//	std::map<Pat, Clr> pt2clr;
	List();
	void Default();

	//  load, import
	bool LoadFromDC(std::string file);  // DC doublecmd.xml
	bool ImportFromTC(std::string file);  // TC color.ini

	//  project file, own
	bool Load(std::string file);
	bool Save(std::string file);

};
