#include "list.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;


List::List()
{
}

void List::Default()
{
    pat.clear();
    clr.clear();

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
		XMLElement* f,*c,*a;
		Pat p;
		f = fi->FirstChildElement("FileMasks");  p.s = f->GetText();
		c = fi->FirstChildElement("Color");		 p.c = atol(c->GetText());
		a = fi->FirstChildElement("Attributes"); //p.a =

		//Clr cl;  cl.c = p.c;
		clr.insert(p.c);

		pat.push_back(p);
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
