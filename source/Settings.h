#pragma once

namespace sf {  class Window;  }


//  App Settings
//------------------------------------------------
class Settings
{
public:
	const static int ver = 60;

	//  main
	Settings();
	void Default();

	bool Load();  // set.xml
	bool Save();


	//  paths  -----
	//  char[] is for imgui
	const static int PathLen = 320;
	char pathSet[PathLen]={0};  // settings file
	char pathProj[PathLen]={0};  // project file

	char pathDCxml[PathLen]={0};  // doublecmd.xml to save into
	char pathDCexe[PathLen]={0};  // to start DC

	char pathTCini[PathLen]={0};  // TC color.ini


	//  dimensions  -----
	float fSplit = 0.27f;   // splitter 0..1
	int   iFontH = 16;      // font height in list
	int   iFontGui = 18;    // font height for Gui
	int   iLineH = 2;       // line spacing
	float fXMargin = 0.7f;  // item x extra spacing

	int   cmbDC = 0;  // import/export combo  DC 0, TC 1
	bool  merge = false;  // merge load, without clear, load into current set


	//  window  -----
	int xwPos = 0, ywPos = 0;
	int xwSize = 1024, ywSize = 768;
	void GetWndDim(sf::Window* wnd);
};
