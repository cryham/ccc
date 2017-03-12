#pragma once
#include <string>


//  App Settings
//------------------------------------------------
class Settings
{
public:
	const int ver = 20;

	//  main
	Settings();
	void Default();

	bool Load(std::string file);  // xml
	bool Save(std::string file);


	//  paths,  char[] is for imgui
	const static int PathLen = 320;
	char pathProj[PathLen]={0};  // project file

	char pathDCxml[PathLen]={0};  // doublecmd.xml to save into
	char pathDCexe[PathLen]={0};  // to start DC

	//  dim
	float fSplit = 0.27f;  // splitter 0..1
	int iFontH = 16;  // font height
	int iLineH = 2;  // line spacing
	float fXMargin = 0.7f;
};
