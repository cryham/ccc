#pragma once
#include "AppDraw.h"
#include "Settings.h"
#include "List.h"
#include "../libs/imgui.h"  // ImVec4
#include <SFML/System.hpp>


class App : public AppDraw
{
public:
	//  main
	//--------------------------
	App();
	bool InitApp();
	void Graph(), Gui(), Help();

	float dt = 0.f, time = 0.f;  // animation


	//  input events
	//--------------------------
	#define EvKey  const sf::Event::KeyEvent& key
		bool KeyDown(EvKey), KeyUp(EvKey);
		void Mods(EvKey);
	#undef EvKey
	bool alt=0, ctrl=0, shift=0;  // mods
	int dLine = 8, dFind = 1;  // multipliers from mods

	void Mouse(int x, int y);
	void Wheel(float d);
	void Resize(uint x, uint y), UpdSplit();


	//  gui util  -----
	void SetupGuiClr();
	void Sep(int y);  // dummy separator
	void Line(const ImVec4& cl);  //--

	float sp;  // spacing for Sep
	const static ImVec4 cl2, cl0;
	SClr HSVtoRGB(float h, float s, float v);


	//  status info  -----
	struct Status
	{
		std::string txt;
		float hue = 0.55f;
		int cnt = 0;
		const int end = 80;  // 60 = 1sec

		void Set(std::string sText, float hue);
	}status;


	//  tabs  -----
	enum ETabs {
		Tab_Edit, Tab_List, Tab_Settings, Tab_ALL };
	const char* tabNames[Tab_ALL] = {
		"F1 Edit", "F2 List", "F3 Settings" };
	int tab = 1;
	bool edFocus = false, findFocus = false;

	//  settings tabs
	enum ESetTabs {
		STab_Paths, STab_Dims, STab_Other, STab_ALL };
	const char* setTabNames[STab_ALL] = {
		"1 Paths", "2 Dimensions", "3 Other" };
	int setTab = 0;


	//  project  -----
	bool Load(), Save();
	//  merge l into cur list, adds only new patterns
	void Merge(const List& l);

	void Export(), Import();
	bool LoadDC(), SaveDC();
	bool LoadTC(), SaveTC();
	bool StartExe();

	Settings set;  //*  Settings


	//  find  -----
	const static int maxPat = 64;
	char sFind[maxPat]={0};  // string to find, options

	bool findCase = false, findWhole = false, findInverse = false;
	void DoFind();  // search
	int iFound = 0, iFoundAll = 0;  // results
	void NextFind(int d);  //  goto next/prev occurence


	//  dimensions
	//--------------------------
	uint xWindow = 600, yWindow = 400;  // window size
	int xSplit = 200;  // spl
	bool bHelp = false;  // show help
	void IncFont(int d);  // change font size

	//  mouse vars
	int xm=0, ym=0, ymo=0, lno=0;  // mouse pos, old
	int mb=0, mbo=0;   // buttons state, old
	bool dragSplit = false, dragSlider = false;  // dragging



	///  List operations
	//----------------------------------------------------
	bool Check();  // true if list empty, quit all operations
	SClr copyClr;
	void CopyClr(), PasteClr();  // copy and paste color

	//  add, del, move
	void AddPat(bool start=false, bool end=false, bool alt=false);
	void DelPat();
	void Erase(int a, int b);
	void Move();

	//  toggle
	void InvDir(), UpdDir(Pat& p);
	void SetClr(bool line=true);
	void InvHide(), InvGroup();


	//  list, edit params
	//--------------------------
	struct Ed  // edit for gui
	{
		int r,g,b;  // clr
		//float h,s,v;  //todo: HSV..
		char pat[maxPat], attr[12];
		bool dir, hide, group;
		int grpSet;  // group set id
		bool onlyDC, onlyTC;
		Ed();
	}ed;

	int iCur = 0;  // list cursor, index
	void SetCur(int d);

	int line = 0;  // page offset, lines
	void IncLine(int d, int end=0);
	void First(bool ctrl), Last(bool ctrl);  // home, end

	int iPick =-1;  // mouse over, id
	int iLineSel =-1;  // selected row, line id

	List li;  //*  List


	//  open dialog for files  ----
	void OpenDialog(), Open(char* path);
	bool opened = false;
	char* pathToSet = nullptr;  // path to set by dialog
	sf::Thread thrOpen;
};
