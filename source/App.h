#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class App
{
public:
	//  main
	//--------------------------
	App();

	bool Init();
	bool KeyDown(const sf::Event::KeyEvent& key);
	void Graph();
	void Quit();


	//  list dimensions
	//--------------------------
	int xe,ye;	  // screen size
	int iFontH;	 // font height
	int lCur, lOfs; // list cursor, page ofset


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
	int Text(int x, int y);

	//  clear rect
	void Rect(int x, int y,
			  int sx, int sy,
			  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b);
};
