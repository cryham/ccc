#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "List.h"


class App
{
public:
	//  main
	//--------------------------
	App();

	bool Init();
	void Graph(), Gui();

	bool KeyDown(const sf::Event::KeyEvent& key);
	bool KeyUp(const sf::Event::KeyEvent& key);
	void Mods(const sf::Event::KeyEvent& key);
	bool alt, ctrl, shift;  // mods

	void Mouse(int x, int y);
	void Wheel(float d);

	void Resize(int x, int y);
	void IncFont(int d);  // change font size


	//  dimensions
	//--------------------------
	int xm,ym;   // mouse
	int mb,wh;

	int xe,ye, xs;   // screen size, splitter
	int iFontH;  // font height
	int iLineH;  // line spacing


	//  list, edit params
	//--------------------------
	struct Ed
	{
		int r,g,b;  // clr
		char pat[64];
		bool dir, lnk, exe;
		Ed();
	}ed;

	int iCur;  // list cursor id,
	int line;  // page ofset lines
	int iPick;  // mouse over cursor
	List li;


	//  sfml drawing
	//--------------------------
	sf::RenderWindow* pWindow;
	sf::Sprite* pBackgr;

	sf::Font* pFont;
	sf::Text text;

	sf::String s;
	sf::Color clr;
	bool bold;


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
