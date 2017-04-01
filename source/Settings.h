#pragma once

namespace sf {  class Window;  }


//  App Settings
//------------------------------------------------
class Settings
{
public:
	const static int ver = 70;  // version

	//  main  -----
	Settings();
	void Default();

	bool Load(), Save();


	//  paths  -----
	//  char[] is for imgui
	const static int PathLen = 320;
	char pathSet[PathLen]={0};   // settings file  ccc.set.xml
	char pathProj[PathLen]={0};  // project file  ccc.xml or custom

	char pathDCxml[PathLen]={0};  // doublecmd.xml to save into
	char pathDCexe[PathLen]={0};  // to start DC

	char pathTCini[PathLen]={0};  // TotalCmd color.ini
	char pathTCexe[PathLen]={0};  // to start TC


	//  dimensions  -----
	float fSplit = 0.22f;   // splitter 0..1
	int   iFontH = 18;      // font height in list
	int   iFontGui = 17;    // font height for Gui
	int   iLineH = 2;       // line spacing
	float fXMargin = 1.7f;  // item extra x spacing
	float fXBackGroup = 0.45f;  // group background length 0..1

	int   cmbDC = 0;      // import/export combo  DC 0, TC 1, also for StartExe
	bool  merge = false;  // merge load, without clear, load into current set


	//  window  -----
	int xwPos = 0, ywPos = 0;
	int xwSize = 1024, ywSize = 768;
	void GetWndDim(sf::Window* wnd);
	bool escQuit = false;
};
