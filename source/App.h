#pragma once
#include "AppDraw.h"
#include "Settings.h"
#include "List.h"
#include "../libs/imgui.h"  // ImVec4


class App : public AppDraw
{
public:
	//  main
	//--------------------------
	App();
	bool Init();
	void Graph(), Gui(), Help();


	//  input events
	//--------------------------
	#define EvKey  const sf::Event::KeyEvent& key
	bool KeyDown(EvKey), KeyUp(EvKey);
	void Mods(EvKey);
	#undef EvKey
	bool alt=0, ctrl=0, shift=0;  // mods

	void Mouse(int x, int y);
	void Wheel(float d);
	void Resize(int x, int y), UpdSplit();


	//  gui util  -----
	void SetupGuiClr();
	void Sep(int y);
	void Line(const ImVec4& cl);
	const static ImVec4 cl2, cl0;


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


	//  project
	bool Load(), Save();
	bool LoadDC(), SaveDC();
	void StartDC();  // extras
	Settings set;  //*  Settings

	//  find
	const static int maxPat = 64;
	char sFind[maxPat]={0};
	int iFound = 0, iFoundAll = 0;
	void DoFind();


	//  list operations
	//--------------------------
	bool Check();  // true if empty, quit all operations
	SClr copyClr;
	void CopyClr(), PasteClr();  // copy and paste color

	//  add, del
	void AddPat(bool start=false, bool end=false);
	void DelPat();
	//  toggle
	//void InvDir();
	void SetClr(bool line=true);


	//  dimensions
	//--------------------------
	int xm=0, ym=0, mb=0, mbo=0;   // mouse pos, btn

	int xWindow =600, yWindow =400, xSplit =200;   // screen size
	bool bHelp = false;
	void IncFont(int d);  // change font size


	//  list, edit params
	//--------------------------
	struct Ed
	{
		int r,g,b;  // clr
		char pat[maxPat], attr[12];
		bool dir, lnk, exe;
		int grp;
		Ed();
	}ed;

	int iCur =0;  // list cursor id
	void SetCur(int d);

	int line =0;  // page ofset lines
	void IncLine(int d, int end=0);
	void First(bool ctrl), Last(bool ctrl);  // home, end
	List li;  //*  List
};
