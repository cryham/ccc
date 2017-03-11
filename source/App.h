#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "List.h"


class App
{
public:
	//  main
	//--------------------------
	bool Init();
	void Graph(), Gui();
	void SetupGuiClr();

	//  input events
	//--------------------------
	bool KeyDown(const sf::Event::KeyEvent& key);
	bool KeyUp(const sf::Event::KeyEvent& key);
	void Mods(const sf::Event::KeyEvent& key);
	bool alt=0, ctrl=0, shift=0;  // mods

	void Mouse(int x, int y);
	void Wheel(float d);

	void Resize(int x, int y);
	void IncFont(int d);  // change font size

	//  project, status
	std::string txtStatus = "F1 Help";  // status info
	float hueStatus = 0.55f;
	int iStatus = 0;
	const int maxStatus = 60;  // 60=1sec

	char proj[340]={0};  // project file
	bool Load();
	bool Save();


	//  dimensions
	//--------------------------
	int xm=0, ym=0, mb=0;   // mouse pos, btn

	int xe =600, ye =400, xs =400;   // screen size, splitter
	int iFontH = 16;  // font height
	int iLineH = 2;  // line spacing


	//  list, edit params
	//--------------------------
	struct Ed
	{
		int r,g,b;  // clr
		char pat[64];
		bool dir, lnk, exe;
		Ed();
	}ed;

	int iCur =0;  // list cursor id,
	int line =0;  // page ofset lines
	int iPick =-1;  // mouse over cursor
	List li;


	//  sfml drawing
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
