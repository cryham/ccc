#include <regex>
#include <fstream>
#include "List.h"
#include "../libs/tinyxml2.h"
#include "Util.h"
#include "App.h"
using namespace std;
using namespace tinyxml2;


//  ctor
List::List()
{	}

void List::Default()
{
	pat.clear();
	clr.clear();
}


//  utils
void SClr::Set(sf::Uint32 u)
{
	r = u       & 0xFF;
	g = u >> 8  & 0xFF;
	b = u >> 16 & 0xFF;
}

sf::Uint32 SClr::Get()
{
	return (b << 16) + (g << 8) + r;
}


//  Update  x,y,l,xw, lines
//------------------------------------------------
void List::Update(int xMax, int xa, int ya)
{
	//if (!app)  return;
	SClr cOld;
	int i, ii = pat.size(), l = 0;
	int x = 0, xw = 0, y = 0;
	lines.clear();
	lines.push_back(0);

	for (i=0; i < ii; ++i)
	{
		Pat& p = pat[i];

		app->str = p.s;  // get text width
		xw = app->Txt(x, y, false) + xa;
		p.xw = xw;

		if (x+xw >= xMax ||
			i > 0 && p.c != cOld)  // new color
		{
			x = 0;  y += ya;
			lines.push_back(i);  ++l;  // next line
		}
		p.x = x;  p.y = y;  p.l = l;
		x += xw;
		cOld = p.c;
	}
}


//  load, import from  DC doublecmd.xml
//------------------------------------------------------------------------------------------------
bool List::LoadDC(string file)
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
			cl = fi->FirstChildElement("Color");	c = atoi(cl->GetText());  q.c.Set(c);
			at = fi->FirstChildElement("Attributes");	q.attr = at->GetText();
			clr.insert(c);

			auto vs = split(q.s, ";");
			for (auto s: vs)
			{	Pat p;
				p.s = s;
				p.c = q.c;
				p.attr = q.attr;
				pat.push_back(p);
			}
		#endif
		fi = fi->NextSiblingElement();
	}
	return true;
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

//  save, export to  DC doublecmd.xml
//  will replace the section in existing xml
//------------------------------------------------
bool List::SaveDC(string file)
{
	if (pat.empty())  return false;

	XMLDocument xml;
	XMLElement* filt = xml.NewElement("FileFilters");

	vector<int> id;
	id.push_back(0);
	int i = 0;
	for (auto& p : pat)
	{
		if (i > 0)
		{
			const Pat& o = pat[i-1];
			if (o.c != p.c)
				id.push_back(i);
		}
		++i;
	}
	id.push_back(pat.size());

	for (int ii=0; ii < id.size()-1; ++ii)
	{
		int i0 = id[ii], i1 = id[ii+1];
		XMLElement* fi = xml.NewElement("Filter");
		string s, n;
		for (int i=i0; i < i1; ++i)
			s += pat[i].s + ";";
		Pat p = pat[i0];  n = s;

		//  name special cases
		#define fnd(s)  p.attr.find(s) != string::npos
		if (fnd("l"))  n = "Link";  else
		if (fnd("d"))  n = "Dir";  else
		if (fnd("x"))  n = "Exe";

		XMLElement* nm = xml.NewElement("Name");		nm->SetText(n.c_str());
		XMLElement* fm = xml.NewElement("FileMasks");	fm->SetText(s.c_str());
		XMLElement* cl = xml.NewElement("Color");		cl->SetText(p.c.Get());
		XMLElement* at = xml.NewElement("Attributes");	at->SetText(p.attr.c_str());
		fi->InsertEndChild(nm);
		fi->InsertEndChild(fm);
		fi->InsertEndChild(cl);
		fi->InsertEndChild(at);
		filt->InsertEndChild(fi);
	}

	if (0)
	{
		xml.InsertEndChild(filt);
		return xml.SaveFile(file.c_str()) == XML_SUCCESS;
	}
	else
	{	char l[1024];
//		ofstream fi;
		ifstream fi;
//		fi.open(file.c_str());
		fi.open("dc.xml");
		if (fi.good())
		{
			fi.getline(l, sizeof(l)-1);
		}

		XMLPrinter printer;
		filt->Accept(&printer);
		const char* fo = printer.CStr();
	}
}

//  load, import from  TC color.ini
bool List::ImportTC(string file)
{
	Default();
	return true;
}


//  load project file, own
//------------------------------------------------------------------------------------------------
bool List::Load(string file)
{
	Default();

	XMLDocument doc;
	XMLError er = doc.LoadFile(file.c_str());
	if (er != XML_SUCCESS)
	{	/*Can't load: "+file);*/  return false;  }

	XMLElement* root = doc.RootElement();
	if (!root)  return false;
	string rn = root->Name();
	if (rn != "ccc")  return false;

	Default();

	///  load Filters
	XMLElement* pt = root->FirstChildElement("Pat");
	if (!pt)  return false;

	while (pt)
	{
		XMLElement* fm,*cl,*at;
		Pat p;  sf::Uint32 c;
		fm = pt->FirstChildElement("s");	p.s = fm->GetText();
		cl = pt->FirstChildElement("c");	c = atoi(cl->GetText());  p.c.Set(c);
		at = pt->FirstChildElement("a");	p.attr = at->GetText();
		clr.insert(c);
		pat.push_back(p);
		pt = pt->NextSiblingElement();
	}
	return true;
}

//  save project file, own
//------------------------------------------------
bool List::Save(string file)
{
	XMLDocument xml;
	XMLElement* root = xml.NewElement("ccc");
	root->SetAttribute("ver", 10);

	for (auto& p : pat)
	{
		XMLElement* fi = xml.NewElement("Pat");
		XMLElement* fm = xml.NewElement("s");	fm->SetText(p.s.c_str());
		XMLElement* cl = xml.NewElement("c");	cl->SetText(p.c.Get());
		XMLElement* at = xml.NewElement("a");	at->SetText(p.attr.c_str());
		fi->InsertEndChild(fm);
		fi->InsertEndChild(cl);
		fi->InsertEndChild(at);
		root->InsertEndChild(fi);
	}

	xml.InsertEndChild(root);
	return xml.SaveFile(file.c_str()) == XML_SUCCESS;
}
