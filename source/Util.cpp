#include "Util.h"
#include <sstream>
#include <iomanip>
#include <regex>
using namespace std;


//  string utils
//------------------------------------------------------------------

string i2s(const int v, const char width)
{
	ostringstream s;
	if (width != 0)  s.width(width);  //s.fill(fill);
	s << fixed << v;
	return s.str();
}

string f2s(const float v, const char precision, const char width)
{
	ostringstream s;
	if (width != 0)  s.width(width);
	s << fixed << setprecision(precision) << v;
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


string strlower(const string& s)
{
	string ss = s;
	transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
	return ss;
}
