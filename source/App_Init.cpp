#ifdef _WIN32
	//#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <Lmcons.h>
#endif
#include "App.h"
#include "FileSystem.h"
#include "../libs/nfd.h"
#include <cstring>
#include <iostream>
using namespace std;


//  edit ctor
//----------------------------------
App::Ed::Ed()
	:r(120), g(120), b(120)
	,dir(false), hide(false)
	,group(false), grpSet(0)
	,onlyDC(false), onlyTC(false)
{
	memset(pat,0,sizeof(pat));
	memset(attr,0,sizeof(attr));
}

//  set size
void App::UpdSplit()
{
	xSplit = static_cast<int>(set.fSplit * xWindow);
}
void App::Resize(uint x, uint y)
{
	xWindow = x;  yWindow = y;
	set.xwSize = x;  set.ywSize = y;
	UpdSplit();
	if (pWindow)
		pWindow->setView(sf::View(sf::FloatRect(0.f, 0.f, xWindow, yWindow)));
}

//  ctor
App::App()
	:thrOpen(&App::OpenDialog, this)
{	}


//  Init
//----------------------------------
bool App::InitApp()
{
	SetupGuiClr();
	li.SetApp(this);

	Load();  // load last proj

	return true;
}


//  Open file dialog
//----------------------------------
void App::OpenDialog()
{
	nfdchar_t *outPath = NULL;
	nfdresult_t res;

	//  get cur path
	string s = pathToSet;
	auto p = s.find_last_of("\\");
	if (p != string::npos)
		s = s.substr(0, p);

	res = NFD_OpenDialog(NULL, s.c_str(), &outPath);

	if (res == NFD_OKAY)
	{
		strcpy(pathToSet, outPath);
		free(outPath);
	}
//	else if (res == NFD_CANCEL)
//		printf("cancel");
//	else
//		printf("Error: %s\n", NFD_GetError());

	opened = false;
}

void App::Open(char* path)
{
	if (opened || !path)
		return;

	pathToSet = path;
	opened = true;
	thrOpen.launch();
}


//  start dc or tc exe
//----------------------------------
bool App::StartExe()
{
	bool dc =  set.cmbDC ?  (alt ? true : false) :
							(alt ? false : true);
	string p = dc ? set.pathDCexe : set.pathTCexe;
	string sDC = dc ? "DC" : "TC";
	string s = string("\"") + p + "\"";
#ifdef _WIN32
	bool er = int(ShellExecute(NULL, "open", s.c_str(), NULL, NULL, SW_SHOWDEFAULT)) <= 32;
#else
	bool er = system(s.c_str()) != 0;  // todo
#endif
	status.Set(er ? "Start "+sDC+" error!" : "Started "+sDC+".", er ? 0.1f : 0.62f);
	return er;
}

//  Load, Save
//----------------------------------
bool App::Load()
{
	bool er;
	if (FileSystem::Exists(set.pathProj))
	{
		er = !li.Load(set.pathProj);
		status.Set(er ? "Load error!" : "Loaded.", er ? 0.2f : 0.42f);
	}else
	{
		cout << "Project file not found: " << set.pathProj << endl
			 << "Loading program's default project." << endl;
		string def = FileSystem::Data() + "/ccc.xml";
		er = !li.Load(def.c_str());
		status.Set(er ? "Load Defaults error!" : "Loaded Defaults.", er ? 0.f : 0.2f);
	}
	SetCur(iCur);  // set gui
	return er;
}
bool App::Save()
{
	bool er = !li.Save(set.pathProj);
	status.Set(er ? "Save error!" : "Saved.", er ? 0.f : 0.55f);
	return er;
}

//  DC  ------------
bool App::LoadDC()
{
	bool er = !li.LoadDC(set.pathDCxml);
	status.Set(er ? "Import DC error!" : "Imported from DC.", er ? 0.2f : 0.42f);
	SetCur(iCur);
	return er;
}
bool App::SaveDC()
{
	bool er = !li.SaveDC(set.pathDCxml);
	status.Set(er ? "Export DC error!" : "Exported into DC.", er ? 0.f : 0.55f);
	return er;
}

//  TC  ------------
bool App::LoadTC()
{
	bool er = !li.LoadTC(set.pathTCini);
	status.Set(er ? "Import TC error!" : "Imported from TC.", er ? 0.2f : 0.50f);
	SetCur(iCur);
	return er;
}
bool App::SaveTC()
{
	bool er = !li.SaveTC(set.pathTCini);
	status.Set(er ? "Export TC error!" : "Exported into TC.", er ? 0.f : 0.60f);
	return er;
}

//  Export Import  DC/TC
//----------------------------------
void App::Export()
{
	if (set.cmbDC==0)
	{	if (alt)  SaveTC();  else  SaveDC();  }else
	{	if (alt)  SaveDC();  else  SaveTC();  }
}

void App::Import()
{
	List l;
	if (set.merge)
		l = li;

	if (set.cmbDC==0)
	{	if (alt)  LoadTC();  else  LoadDC();  }else
	{	if (alt)  LoadDC();  else  LoadTC();  }
	SetCur(iCur);

	if (set.merge)
		Merge(l);
}

//  merge
void App::Merge(const List& l)
{
	int jj = li.pat.size();
	int ii = l.pat.size();
	for (int i = 0; i < ii; ++i)
	{
		const Pat& p = l.pat[i];  // new list

		//  search for it in cur list
		bool found = false;  //int jf = -1;
		int j = 0;
		while (!found && j < jj)
		{
			if (li.pat[j].s == p.s)
				found = true;
			else
				++j;
		}
		if (!found)  // add if new
			li.pat.push_back(p);
	}
}
