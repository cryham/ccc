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
	void Sep(int y);  // dummy separator
	void Line(const ImVec4& cl);  //--

	float sp;  // spacing for Sep
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
	bool LoadTC(), SaveTC();
	void Export(), Import();
	void Merge(const List& l);  // merge l into cur list, add only new patterns

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

	//  add, del, move
	void AddPat(bool start=false, bool end=false, bool alt=false);
	void DelPat();
	void Erase(int a, int b);
	void Move();

	//  toggle
	void InvDir();
	void SetClr(bool line=true);


	//  dimensions
	//--------------------------
	int xm=0, ym=0;  // mouse pos
	int mb=0, mbo=0;   // mouse buttons state, old

	int xWindow =600, yWindow =400, xSplit =200;   // screen size
	bool bHelp = false;
	void IncFont(int d);  // change font size


	//  list, edit params
	//--------------------------
	struct Ed  // edit for gui
	{
		int r,g,b;  // clr
		//float h,s,v;
		char pat[maxPat], attr[12];
		bool dir;
		//int grp;
		Ed();
	}ed;

	int iCur =0;  // list cursor id
	void SetCur(int d);

	int line =0;  // page ofset lines
	void IncLine(int d, int end=0);
	void First(bool ctrl), Last(bool ctrl);  // home, end

	int iPick =-1;  // mouse over, id
	int iLineSel =-1;  // selected row, line id

	List li;  //*  List
};
