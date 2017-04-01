#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <Lmcons.h>
#endif
#include <SFML/Window.hpp>
#include "Settings.h"
#include "../libs/tinyxml2.h"
#include "Util.h"
using namespace std;  using namespace tinyxml2;


//  ctor
Settings::Settings()
{
	memset(pathSet,0,sizeof(pathSet));
	memset(pathProj,0,sizeof(pathProj));

	memset(pathDCxml,0,sizeof(pathDCxml));  memset(pathDCexe,0,sizeof(pathDCexe));
	memset(pathTCini,0,sizeof(pathTCini));  memset(pathTCexe,0,sizeof(pathTCexe));
	Default();
}

void Settings::GetWndDim(sf::Window* wnd)
{
	xwPos = wnd->getPosition().x;
	ywPos = wnd->getPosition().y;
	xwSize = wnd->getSize().x;
	ywSize = wnd->getSize().y;
}


//  Defaults, init paths
//------------------------------------------------------------------------------------------------
void Settings::Default()
{
	fSplit = 0.22f;
	iFontH = 18;
	iFontGui = 17;
	iLineH = 2;

	fXMargin = 1.7f;
	fXBackGroup = 0.45f;

	cmbDC = 0;
	merge = false;
	escQuit = false;

	strcpy(pathSet, "ccc.set.xml");
	strcpy(pathProj, "ccc.xml");

#ifdef _WIN32
	char username[UNLEN+1];
	DWORD username_len = UNLEN+1;
	GetUserName(username, &username_len);

	string usr = string("c:\\Users\\")+username+"\\AppData\\Roaming\\doublecmd\\doublecmd.xml";
	strcpy(pathDCxml, usr.c_str());
	strcpy(pathDCexe, "c:\\Program Files\\Double Commander\\doublecmd.exe");

	strcpy(pathTCini, "color.ini");
	strcpy(pathTCexe, "c:\\Program Files\\Total Commander\\totalcmd.exe");
#else
	//todo
	strcpy(pathDC, "");
	strcpy(pathDCexe, "doublecmd");
#endif
}


///  Load
//------------------------------------------------------------------------------------------------
bool Settings::Load()
{
	Default();

	XMLDocument doc;
	XMLError er = doc.LoadFile(pathSet);
	if (er != XML_SUCCESS)
	{	/*Can't load: "+file);*/  return false;  }

	XMLElement* root = doc.RootElement();
	if (!root)  return false;
	string rn = root->Name();
	if (rn != "ccc_set")  return false;

	Default();

	XMLElement* e;  const char* a;

	//  paths
	e = root->FirstChildElement("pathProj");   if (e){  a = e->Attribute("p");  if (a)  strcpy(pathProj,a);  }
	e = root->FirstChildElement("pathDCxml");  if (e){  a = e->Attribute("p");  if (a)  strcpy(pathDCxml,a);  }
	e = root->FirstChildElement("pathDCexe");  if (e){  a = e->Attribute("p");  if (a)  strcpy(pathDCexe,a);  }
	e = root->FirstChildElement("pathTCini");  if (e){  a = e->Attribute("p");  if (a)  strcpy(pathTCini,a);  }
	e = root->FirstChildElement("pathTCexe");  if (e){  a = e->Attribute("p");  if (a)  strcpy(pathTCexe,a);  }

	e = root->FirstChildElement("dim");
	if (e)
	{	a = e->Attribute("fSplit");  if (a)  fSplit = atof(a);
		a = e->Attribute("iFontH");  if (a)  iFontH = atoi(a);
		a = e->Attribute("iLineH");  if (a)  iLineH = atoi(a);
		a = e->Attribute("iFontGui");  if (a)  iFontGui = atoi(a);

		a = e->Attribute("fXMargin");  if (a)  fXMargin = atof(a);
		a = e->Attribute("fXBackGroup");  if (a)  fXBackGroup = atof(a);

		a = e->Attribute("cmbDC");  if (a)  cmbDC = atoi(a);
		a = e->Attribute("merge");  if (a)  merge = atoi(a) > 0? true: false;
	}
	e = root->FirstChildElement("window");
	if (e)
	{	a = e->Attribute("x");  if (a)  xwPos = atoi(a);
		a = e->Attribute("y");  if (a)  ywPos = atoi(a);
		a = e->Attribute("sx");  if (a)  xwSize = atoi(a);
		a = e->Attribute("sy");  if (a)  ywSize = atoi(a);
		a = e->Attribute("escQuit");  if (a)  escQuit = atoi(a) >0? true: false;
	}
	return true;
}

///  Save
//------------------------------------------------------------------------------------------------
bool Settings::Save()
{
	XMLDocument xml;
	XMLElement* root = xml.NewElement("ccc_set");
	root->SetAttribute("ver", ver);
	XMLElement* e;

	//  paths
	e = xml.NewElement("pathProj");   e->SetAttribute("p", pathProj);  root->InsertEndChild(e);
	e = xml.NewElement("pathDCxml");  e->SetAttribute("p", pathDCxml);  root->InsertEndChild(e);
	e = xml.NewElement("pathDCexe");  e->SetAttribute("p", pathDCexe);  root->InsertEndChild(e);
	e = xml.NewElement("pathTCini");  e->SetAttribute("p", pathTCini);  root->InsertEndChild(e);
	e = xml.NewElement("pathTCexe");  e->SetAttribute("p", pathTCexe);  root->InsertEndChild(e);

	e = xml.NewElement("dim");
		e->SetAttribute("fSplit", f2s(fSplit,3).c_str());
		e->SetAttribute("iFontH", iFontH);
		e->SetAttribute("iLineH", iLineH);
		e->SetAttribute("iFontGui", iFontGui);

		e->SetAttribute("fXMargin", f2s(fXMargin,3).c_str());
		e->SetAttribute("fXBackGroup", f2s(fXBackGroup,3).c_str());

		e->SetAttribute("cmbDC", cmbDC);
		e->SetAttribute("merge", merge ? 1 : 0);
	root->InsertEndChild(e);

	e = xml.NewElement("window");
		e->SetAttribute("x", xwPos);
		e->SetAttribute("y", ywPos);
		e->SetAttribute("sx", xwSize);
		e->SetAttribute("sy", ywSize);
		e->SetAttribute("escQuit", escQuit ? 1 : 0);
	root->InsertEndChild(e);

	xml.InsertEndChild(root);
	return xml.SaveFile(pathSet) == XML_SUCCESS;
}
