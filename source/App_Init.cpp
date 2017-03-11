#include "App.h"
#include <cstring>


//  edit ctor
App::Ed::Ed()
	:r(0), g(0), b(0)
	,dir(false), lnk(false), exe(false)
{
	memset(pat,0,sizeof(pat));
	memset(attr,0,sizeof(attr));
}

//  set size
void App::Resize(int x, int y)
{
	xe = x;  ye = y;
	xs = xe * 5/8;  // splitter
}

//  Init
//------------------------------------------------------------------
bool App::Init()
{
	SetupGuiClr();

	li.SetApp(this);

	li.LoadDC("doublecmd.xml");
	strcpy(proj, "ccc.xml");

	return true;
}

bool App::Load()
{
	bool er = !li.Load(proj);
	txtStatus = er ? "Load error!" : "Loaded.";
	hueStatus = er ? 0.2f : 0.42f;
	iStatus = 0;
}
bool App::Save()
{
	bool er = !li.Save(proj);
	txtStatus = er ? "Save error!" : "Saved.";
	hueStatus = er ? 0.f : 0.55f;
	iStatus = 0;
}
