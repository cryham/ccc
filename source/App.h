#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "List.h"


class App
{
public:
	//  main
	//--------------------------
	App();
	bool Init();
	void Graph(), Gui();
	void SetupGuiClr();

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


	//  status
	std::string txtStatus;  // status info
	float hueStatus = 0.55f;
	int iStatus = 0;
	const int maxStatus = 60;  // 60=1sec

	//  tabs
	enum ETabs {
		Tab_Edit, Tab_List, Tab_Settings, Tab_Help, Tab_ALL };
	const char* tabNames[Tab_ALL] = {
		"F1 Edit", "F2 List", "Settings", "Help"};
	int tab = 1;
	bool edFocus = false;


	//  project
	bool Load(), Save();
	//  extras
	void StartDC();
	Settings set;


	//  list operations
	//--------------------------
	bool Check();  // true if empty, quit all operations
	SClr copyClr;
	void CopyClr(), SetClr();  // copy and paste color

	//  toggle
	void InvDir();
	//  add, del
	void AddPat(bool start=false, bool end=false);
	void DelPat();


	//  dimensions
	//--------------------------
	int xm=0, ym=0, mb=0;   // mouse pos, btn

	int xWindow =600, yWindow =400, xSplit =200;   // screen size
	void IncFont(int d);  // change font size


	//  list, edit params
	//--------------------------
	struct Ed
	{
		int r,g,b;  // clr
		char pat[64], attr[12];
		bool dir, lnk, exe;
		int grp;
		Ed();
	}ed;

	int iCur =0;  // list cursor id,
	void SetCur(int d), IncLine(int d);

	int line =0;  // page ofset lines
	//int iPick =-1;  // mouse over cursor
	List li;


	//  sfml draw
	//--------------------------
	sf::RenderWindow* pWindow = nullptr;
	sf::Sprite* pBackgr = nullptr;

	sf::Font* pFont = nullptr;
	sf::Text text;

	sf::String str;
	sf::Color clr;
	bool bold = false;


	//  set text color
	//--------------------------
	void Clr(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
	{
		clr = sf::Color(r,g,b);
	}
	void Clr(const SClr& c)
	{
		clr = sf::Color(c.r, c.g, c.b);
	}

	//  write out text, from s
	//  returns width, x advance
	int Txt(int x, int y, bool draw=true);

	//  clear rect
	void Rect(int x, int y,  int sx, int sy,  const SClr& c);
	void Rect(int x, int y,  int sx, int sy,  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
	//  frame rect
	void Frame(int x, int y,  int sx, int sy,  int d,  const SClr& c);
	void Frame(int x, int y,  int sx, int sy,  int d,  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
};
