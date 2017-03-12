#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <Lmcons.h>
#endif
#include "Settings.h"
#include "../libs/tinyxml2.h"
//#include "Util.h"
using namespace std;
using namespace tinyxml2;


//  ctor
Settings::Settings()
{
	memset(pathProj,0,sizeof(pathProj));
	memset(pathDCxml,0,sizeof(pathDCxml));
	memset(pathDCexe,0,sizeof(pathDCexe));
	Default();
}

void Settings::Default()
{
	fSplit = 0.27f;
	iFontH = 16;
	iLineH = 2;

	strcpy(pathProj, "ccc.xml");

#ifdef _WIN32
	char username[UNLEN+1];
	DWORD username_len = UNLEN+1;
	GetUserName(username, &username_len);
	string usr = string("c:\\Users\\")+username+"\\AppData\\Roaming\\doublecmd";
	strcpy(pathDCxml, usr.c_str());

	strcpy(pathDCexe, "c:\\Program Files\\Double Commander\\doublecmd.exe");
#else
	//todo
	strcpy(pathDC, "");
	strcpy(pathDCexe, "doublecmd");
#endif
}


//  load project file, own
//------------------------------------------------------------------------------------------------
bool Settings::Load(string file)
{
	Default();

	XMLDocument doc;
	XMLError er = doc.LoadFile(file.c_str());
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
	e = root->FirstChildElement("pathDCexe");  if (e){  a = e->Attribute("p");  if (a)  strcpy(pathDCexe,a);  }
	e = root->FirstChildElement("pathDCxml");  if (e){  a = e->Attribute("p");  if (a)  strcpy(pathDCxml,a);  }

	return true;
}

//  save project file, own
//------------------------------------------------
bool Settings::Save(string file)
{
	XMLDocument xml;
	XMLElement* root = xml.NewElement("ccc_set");
	root->SetAttribute("ver", ver);
	XMLElement* e;

	//  paths
	e = xml.NewElement("pathProj");   e->SetAttribute("p", pathProj);  root->InsertEndChild(e);
	e = xml.NewElement("pathDCexe");  e->SetAttribute("p", pathDCexe);  root->InsertEndChild(e);
	e = xml.NewElement("pathDCxml");  e->SetAttribute("p", pathDCxml);  root->InsertEndChild(e);

	xml.InsertEndChild(root);
	return xml.SaveFile(file.c_str()) == XML_SUCCESS;
}
