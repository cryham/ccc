#include "Util.h"
#include <sstream>
#include <iomanip>
#include <regex>
using namespace std;


//  string utils
//------------------------------------------------------------------

std::string i2s(const int v, const char width)
{
	std::ostringstream s;
	if (width != 0)  s.width(width);  //s.fill(fill);
	s << std::fixed << v;
	return s.str();
}

std::string f2s(const float v, const char precision, const char width)
{
	std::ostringstream s;
	if (width != 0)  s.width(width);
	s << std::fixed << std::setprecision(precision) << v;
	return s.str();
}


vector<string> split(const string& s, const string& reg)
{
	regex re(reg);
	sregex_token_iterator
		first{s.begin(), s.end(), re, -1},  // -1 split
		last;
	return {first, last};
}
