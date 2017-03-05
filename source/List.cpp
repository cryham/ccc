#include <regex>
#include "list.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;


//  ctor
List::List()
{
}

void List::Default()
{
	pat.clear();
	clr.clear();
}


//  utils
void Pat::SetClr(sf::Uint32 c)
{
	r = c       & 0xFF;
	g = c >> 8  & 0xFF;
	b = c >> 16 & 0xFF;
}

vector<string> split(const string& s, const string& reg)
{
	regex re(reg);
	sregex_token_iterator
		first{s.begin(), s.end(), re, -1},  // -1 split
		last;
	return {first, last};
}


//  load, import from  DC doublecmd.xml
//------------------------------------------------
bool List::LoadFromDC(std::string file)
{
	XMLDocument doc;
	XMLError er = doc.LoadFile(file.c_str());
	if (er != XML_SUCCESS)
	{	/*Can't load: "+file);*/  return false;  }

	XMLElement* root = doc.RootElement();
	if (!root)  return false;
	string rn = root->Name();
	if (rn != "doublecmd")  return false;
	XMLElement* clrs = root->FirstChildElement("Colors");
	if (!clrs)  return false;
	XMLElement* filt = clrs->FirstChildElement("FileFilters");
	if (!filt)  return false;

	Default();

	///  load Filters
	XMLElement* fi = filt->FirstChildElement("Filter");
	if (!fi)  return false;

	while (fi)
	{
		XMLElement* fm,*cl,*at;
		#if 0  // single line
			Pat p;
			fm = fi->FirstChildElement("FileMasks");	p.s = fm->GetText();
			cl = fi->FirstChildElement("Color");		p.SetClr(atoi(cl->GetText()));
			at = fi->FirstChildElement("Attributes");	p.attr = at->GetText();
			pat.push_back(p);
		#else  // split each pattern
			Pat q;  sf::Uint32 c;
			fm = fi->FirstChildElement("FileMasks");	q.s = fm->GetText();
			cl = fi->FirstChildElement("Color");	c = atoi(cl->GetText());  q.SetClr(c);
			at = fi->FirstChildElement("Attributes");	q.attr = at->GetText();
			clr.insert(c);

			auto vs = split(q.s, ";");
			for (auto s: vs)
			{	Pat p;
				p.s = s;
				p.r = q.r;  p.g = q.g;  p.b = q.b;
				p.attr = q.attr;
				pat.push_back(p);
			}
		#endif
		fi = fi->NextSiblingElement();
	}
/*
	<doublecmd ..>
	  <Configuration ..>
	  <Colors>
		<FileFilters>
		  <Filter>
			<Name>..</Name>
			<FileMasks>*=.flac;*.d;</FileMasks>
			<Color>10049581</Color>
			<Attributes>**</Attributes>
		  </Filter>
*/
	return true;
}

//  save, export to  DC doublecmd.xml
//------------------------------------------------
bool List::SaveToDC(std::string file)
{
	XMLDocument xml;
	XMLElement* root = xml.NewElement("FileFilters");

	XMLElement* ver = xml.NewElement("Filter");
		ver->SetAttribute("num",	"12");
	root->InsertEndChild(ver);

	xml.InsertEndChild(root);
	return xml.SaveFile(file.c_str());
}

//  load, import from  TC color.ini
bool List::ImportFromTC(std::string file)
{
	Default();
	return true;
}


//  load project file, own
//------------------------------------------------
bool List::Load(std::string file)
{
	Default();

	XMLDocument doc;
	doc.LoadFile(file.c_str());

	doc.RootElement();

	return true;
}

//  save project file, own
bool List::Save(std::string file)
{
	XMLDocument doc;
	doc.SaveFile(file.c_str());
	return true;
}
