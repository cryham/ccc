#include "App.h"
#include <sstream>
#include <iomanip>


//  ctor
App::App()
	:pWindow(NULL), pFont(NULL), xe(100), ye(100), bold(false)
	,xm(0), ym(0)
{
	iFontH = 16;  // font h

	lOfs = lCur = 0;
}

//  Init
//------------------------------------------------------------------
bool App::Init()
{
	li.LoadFromDC("doublecmd.xml");

	return true;
}


//  utils
//------------------------------------------------------------------

//  write out text
int App::Text(int x, int y)
{
	//if (!window)  return;
	text.setString(s);
	text.setStyle(bold ? sf::Text::Bold : sf::Text::Regular);
	text.setColor(clr);
	text.setPosition(x, y);
	pWindow->draw(text);
	return text.getLocalBounds().width;  // advance x pos
}

//  clear rect
void App::Rect(int x, int y,
		  int sx, int sy,
		  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
	//if (!pBackgr)  return;
	pBackgr->setScale(sx-x, sy-y);
	pBackgr->setPosition(x, y);
	pBackgr->setColor(sf::Color(b, g, r));
	pWindow->draw(*pBackgr);
}


std::string i2s(const int v, const char width)
{
	std::ostringstream s;
	if (width != 0)  s.width(width);  //s.fill(fill);
	s << std::fixed << v;
	return s.str();
}
std::string f2s(const float v, const char precision, const char width)
{
	std::ostringstream s;
	if (width != 0)  s.width(width);
	s << std::fixed << std::setprecision(precision) << v;
	return s.str();
}
