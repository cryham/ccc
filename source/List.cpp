#include <regex>
#include <fstream>
#include "List.h"
#include "../libs/tinyxml2.h"
#include "Util.h"
#include "App.h"
#include "Settings.h"
using namespace std;  using namespace tinyxml2;


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

void Pat::SetDir(bool d)
{
	dir = d;
	//  dir and attr has no d
	if (d && (attr == "**" || attr.empty()))
		attr = "d*";
	else
	if (!d && (attr == "d*" || attr.empty()))
		attr = "**";
}



//  Update  x,y,l,xw, lines
//------------------------------------------------
void List::Update(int xMin, int xMax, int xa, int ya)
{
	//if (!app)  return;
	SClr cOld;
	int i, ii = pat.size(), l = 0;
	int x = xMin, xw = 0, y = 0;
	lines.clear();
	lines.push_back(0);
	bool groupHide = false;

	for (i=0; i < ii; ++i)
	{
		Pat& p = pat[i];
		//  update group hide for all
		if (p.group)
			groupHide = p.hide;
		p.hideByGrp = groupHide;

		app->str = p.s;  // get text width
		xw = app->Txt(x, y, false) + xa;
		p.xw = xw;

		if (x+xw >= xMax ||
			i > 0 && p.c != cOld)  // new color
		{
			x = xMin;  y += ya;
			lines.push_back(i);  ++l;  // next line
		}
		p.x = x;  p.y = y;  p.l = l;
		x += xw;
		cOld = p.c;
	}
}

//  line length
int List::LineLen(int id)
{
	if (pat.empty())  return -1;
	int last = lines.size()-1, next = id+1;
	int end = next <= last ? lines[next] : pat.size();  // end of cur line
	return end - lines[id];
}


//  load, import from  DC doublecmd.xml
//------------------------------------------------------------------------------------------------
bool List::LoadDC(const char* file)
{
	XMLDocument doc;
	XMLError er = doc.LoadFile(file);
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
	XMLElement* fi = filt->FirstChildElement("Filter"), *e;
	if (!fi)  return false;

	while (fi)
	{
		Pat q;  sf::Uint32 c;
		e = fi->FirstChildElement("FileMasks");		if (e)  q.s = e->GetText();
		e = fi->FirstChildElement("Color");			if (e){  c = atoi(e->GetText());  q.c.Set(c);  }
		e = fi->FirstChildElement("Attributes");	if (e)  q.attr = e->GetText();
		clr.insert(c);

		//  split each pattern
		auto vs = split(q.s, ";");
		for (auto& s : vs)
		{	Pat p;
			p.s = s;  p.c = q.c;
			p.attr = q.attr;
			pat.push_back(p);
		}
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
//------------------------------------------------------------------------------------------------
bool List::SaveDC(const char* file)
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
		{	const Pat& o = pat[i-1];
			if (o.c != p.c)
				id.push_back(i);
		}	++i;
	}
	id.push_back(pat.size());

	for (int ii=0; ii < id.size()-1; ++ii)
	{
		int i0 = id[ii], i1 = id[ii+1];

		string s, n;
		for (int i=i0; i < i1; ++i)
		{
			if (pat[i].Visible() && !pat[i].group)  //*
				s += pat[i].s + ";";
		}
		Pat p = pat[i0];  n = s;

		if (n.empty())
			continue;
		XMLElement* fi = xml.NewElement("Filter"), *e;

		//  name special cases
		#define Find(s)  p.attr.find(s) != string::npos
		if (n == "*;")
		{
			if (Find("l"))  n = "Link";  else
			if (Find("d"))  n = "Dir";  else
			if (Find("x"))  n = "Exe";
		}
		#undef Find

		e = xml.NewElement("Name");			e->SetText(n.c_str());  fi->InsertEndChild(e);
		e = xml.NewElement("FileMasks");	e->SetText(s.c_str());  fi->InsertEndChild(e);
		e = xml.NewElement("Color");		e->SetText(p.c.Get());  fi->InsertEndChild(e);
		e = xml.NewElement("Attributes");	e->SetText(p.attr.c_str());  fi->InsertEndChild(e);
		filt->InsertEndChild(fi);
	}

	//  save  --------------
	//  original dc xml
	ifstream fi;
	fi.open(file);  if (!fi.good())  return false;
	//  temp save
	ofstream fo;
	string ss = string(file) + "1";
	const char* file1 = ss.c_str();
	fo.open(file1);  if (!fo.good())  return false;

	//  read lines
	bool ff = false;
	char l[1024];
	while (fi.good())
	{
		fi.getline(l, sizeof(l)-1);
		if (strstr(l, "<FileFilters>"))
		{	ff = true;
			//  write our section instead
			XMLPrinter printer;
			filt->Accept(&printer);
			const char* fs = printer.CStr();
			fo << fs << endl;
		}else
		if (strstr(l, "</FileFilters>"))
			ff = false;
		else
		if (!ff && l[0]!=0)
			fo << l << endl;  // write line
	}
	fi.close();
	fo.close();
	//  replace old with new
	remove(file);
	rename(file1, file);
	return true;
}


//  load project file, own
//------------------------------------------------------------------------------------------------
bool List::Load(const char* file)
{
	Default();

	XMLDocument doc;
	XMLError er = doc.LoadFile(file);
	if (er != XML_SUCCESS)
	{	/*Can't load: "+file);*/  return false;  }

	XMLElement* root = doc.RootElement();
	if (!root)  return false;
	string rn = root->Name();
	if (rn != "ccc")  return false;

	Default();

	///  load Filters
	XMLElement* pt = root->FirstChildElement("p");
	if (!pt)  return false;
	const char* a;

	while (pt)
	{
		Pat p;
		a = pt->Attribute("gr");  p.group = atoi(a) > 0;
		if (p.group)
		{
			a = pt->Attribute("s");  p.s = a;
			a = pt->Attribute("h");  p.hide = atoi(a) > 0;
		}else
		{
			a = pt->Attribute("r");  p.c.r = atoi(a);
			a = pt->Attribute("g");  p.c.g = atoi(a);
			a = pt->Attribute("b");  p.c.b = atoi(a);

			a = pt->Attribute("s");  p.s = a;
			a = pt->Attribute("a");  p.attr = a;
			p.dir = p.attr == "d*";  // set dir from attr

			a = pt->Attribute("h");  p.hide = a && atoi(a) > 0;
		}

		clr.insert(p.c.Get());
		pat.push_back(p);
		pt = pt->NextSiblingElement();
	}
	return true;
}

//  save project file, own
//------------------------------------------------
bool List::Save(const char* file)
{
	XMLDocument xml;
	XMLElement* root = xml.NewElement("ccc");
	root->SetAttribute("ver", Settings::ver);

	for (auto& p : pat)
	{
		XMLElement* pt = xml.NewElement("p");
		if (p.group)
		{
			pt->SetAttribute("s", p.s.c_str());

			pt->SetAttribute("h", p.hide? 1: 0);
			pt->SetAttribute("gr", 1);
		}else
		{
			pt->SetAttribute("r", i2s(p.c.r,3).c_str());
			pt->SetAttribute("g", i2s(p.c.g,3).c_str());
			pt->SetAttribute("b", i2s(p.c.b,3).c_str());

			pt->SetAttribute("s", p.s.c_str());
			pt->SetAttribute("a", p.attr.c_str());

			if (p.hide)
				pt->SetAttribute("h", 1);
			//pt->SetAttribute("gr", p.gr? 1: 0);
		}
		root->InsertEndChild(pt);
	}

	xml.InsertEndChild(root);
	return xml.SaveFile(file) == XML_SUCCESS;
}


//  load, import from  TC color.ini
//------------------------------------------------------------------------------------------------
bool List::LoadTC(const char* file)
{
	ifstream fi;
	fi.open(file);  if (!fi.good())  return false;

	Default();

	//  read lines
	char l[1024], sPat[512]={0}, sClr[32]={0};
	int id=0;
	while (fi.good())
	{
		fi.getline(l, sizeof(l)-1);

		if (!strstr(l, "ColorFilter"))  continue;

		if (strstr(l, "Color="))
		{
			sscanf(l, "ColorFilter%dColor=%s", &id, sClr);

			//  clr
			sf::Uint32 u = atoi(sClr);
			SClr c;  c.Set(u);

			//  split each pattern
			auto vs = split(sPat, ";");
			for (auto& s : vs)
			{	Pat p;
				p.s = s;  p.c = c;
				//p.attr = q.attr;
				pat.push_back(p);
			}
		}
		else
		{	//sscanf(l, "ColorFilter%d=%s", &id, sPat);  // can't read "
			string s(l);
			auto p = s.find('=');
			if (p != string::npos)
				s = s.substr(p+1);
			strcpy(sPat, s.c_str());
		}
	}
	return true;
}

/*
	ColorFilter1=*+*.;*up.;*#.;
	ColorFilter1Color=16753488
*/

//  save, export to  TC color.ini
//------------------------------------------------------------------------------------------------
bool List::SaveTC(const char* file)
{
	if (pat.empty())  return false;

	//  original tc ini
	ifstream fi;
	fi.open(file);  if (!fi.good())  return false;
	//  temp save
	ofstream fo;
	string ss = string(file) + "1";
	const char* file1 = ss.c_str();
	fo.open(file1);  if (!fo.good())  return false;

	//  read lines
	bool ff = true;
	char l[1024];
	while (fi.good() && ff)
	{
		fi.getline(l, sizeof(l)-1);
		if (strstr(l, "ColorFilter"))
			ff = false;  // copy beginning, until found
		else
			fo << l << endl;  // write line
	}
	fi.close();

	vector<int> id;
	id.push_back(0);
	int i = 0;
	for (auto& p : pat)
	{
		if (i > 0)
		{	const Pat& o = pat[i-1];
			if (o.c != p.c)
				id.push_back(i);
		}	++i;
	}
	id.push_back(pat.size());

	int j = 1;
	for (int ii=0; ii < id.size()-1; ++ii)
	{
		int i0 = id[ii], i1 = id[ii+1];

		string s;
		for (int i=i0; i < i1; ++i)
		if (pat[i].Visible())
			s += pat[i].s + ";";
		Pat p = pat[i0];

		if (!s.empty())
		{
			fo << "ColorFilter" << j << "=" << s.c_str() << endl;
			fo << "ColorFilter" << j << "Color=" << p.c.Get() << endl;
			++j;	
		}
	}
	fo.close();

	//  replace old with new
	bool ok = true;
	if (remove(file)!=0)  ok = false;
	if (rename(file1, file)!=0)  ok = false;
	return ok;
}
