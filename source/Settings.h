#pragma once
//#include <string>

namespace sf {  class Window;  }


//  App Settings
//------------------------------------------------
class Settings
{
public:
	const int ver = 40;

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


	//  dimensions  -----
	float fSplit = 0.27f;   // splitter 0..1
	int   iFontH = 16;      // font height
	int   iLineH = 2;       // line spacing
	float fXMargin = 0.7f;  // item x extra spacing

	//  window  -----
	int xwPos=0, ywPos=0;
	int xwSize=1024, ywSize=768;
	void GetWndDim(sf::Window* wnd);
};
