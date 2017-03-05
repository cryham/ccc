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
	void Graph();
	void Quit();

	bool KeyDown(const sf::Event::KeyEvent& key);
	void Mouse(int x, int y);

	void IncFont(int d);  // change font size


	//  list dimensions
	//--------------------------
	int xm,ym;   // mouse
	int mb;

	int xe,ye;   // screen size
	int iFontH;  // font height

	int lCur, lOfs;  // list cursor, page ofset
	int lPick;  // mouse over cursor
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

	//  write out text, from s
	//  returns width, x advance
	int Text(int x, int y, bool draw=true);

	//  clear rect
	void Rect(int x, int y,  int sx, int sy,
			  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
	//  frame rect
	void Frame(int x, int y,  int sx, int sy,  int d,
			  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
};


//  util  format int, float to string
std::string i2s(const int v, const char width=0/*, const char fill=' '*/);
std::string f2s(const float v, const char precision=2, const char width=4);
