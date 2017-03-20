#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "List.h"


class AppDraw
{
public:
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
	void Frame(int x, int y,  int sx, int sy,  int d,  bool le, bool ri,  const SClr& c);
	void Frame(int x, int y,  int sx, int sy,  int d,  bool le, bool ri,  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
};
