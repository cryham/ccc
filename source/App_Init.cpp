#ifdef _WIN32
	//#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <Lmcons.h>
#endif
#include "App.h"
#include <cstring>
using namespace std;


//  edit ctor
App::Ed::Ed()
	:r(0), g(0), b(0)
	,dir(false), lnk(false), exe(false)
	,grp(0)
{
	memset(pat,0,sizeof(pat));
	memset(attr,0,sizeof(attr));
}

//  set size
void App::UpdSplit()
{
	xSplit = set.fSplit * xWindow;
}
void App::Resize(int x, int y)
{
	xWindow = x;  yWindow = y;
	set.xwSize = x;  set.ywSize = y;
	UpdSplit();
	if (pWindow)
		pWindow->setView(sf::View(sf::FloatRect(0.f, 0.f, xWindow, yWindow)));
}

//  ctor
App::App()
{	}

//  Init
//----------------------------------
bool App::Init()
{
	SetupGuiClr();
	li.SetApp(this);

	Load();  // load last proj
	SetCur(0);  // set gui

	return true;
}

//  extras
void App::StartDC()
{
	string s = string("\"") + set.pathDCexe + "\"";
#ifdef _WIN32
	ShellExecute(NULL, "open", s.c_str(), NULL, NULL, SW_SHOWDEFAULT);
#else
	system(s.c_str());
#endif
}

//  Load, Save
//----------------------------------
bool App::Load()
{
	bool er = !li.Load(set.pathProj);
	status.Set(er ? "Load error!" : "Loaded.", er ? 0.2f : 0.42f);
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
	status.Set(er ? "Load DC error!" : "Loaded DC.", er ? 0.2f : 0.42f);
	return er;
}

bool App::SaveDC()
{
	bool er = !li.SaveDC(set.pathDCxml);
	status.Set(er ? "Save DC error!" : "Saved DC.", er ? 0.f : 0.55f);
	return er;
}

//  TC  ------------
bool App::LoadTC()
{
	bool er = !li.LoadTC(set.pathTCini);
	status.Set(er ? "Load TC error!" : "Loaded TC.", er ? 0.2f : 0.42f);
	return er;
}

bool App::SaveTC()
{
	bool er = !li.SaveTC(set.pathTCini);
	status.Set(er ? "Save TC error!" : "Saved TC.", er ? 0.f : 0.55f);
	return er;
}
