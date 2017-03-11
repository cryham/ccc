#include "App.h"
#include <cstring>


//  ctor
App::App()
	:pWindow(nullptr), pBackgr(nullptr), pFont(nullptr)
	,xe(100),ye(100), xs(xe/2)
	,iFontH(16), bold(false)
	,xm(0),ym(0), mb(0), wh(0)
	,alt(false),ctrl(false),shift(false)
{
	iCur = 0;  line = 0;  iPick = -1;
}

//  edit ctor
App::Ed::Ed()
	:r(0), g(0), b(0)
	,dir(false), lnk(false), exe(false)
{
	memset(pat,0,sizeof(pat));
}

//  set size
void App::Resize(int x, int y)
{
	xe = x;  ye = y;
	xs = xe * 5/8;  // splitter
}

//  Init
//------------------------------------------------------------------
bool App::Init()
{
	li.SetApp(this);
	li.LoadDC("doublecmd.xml");

	return true;
}


//  draw utils
//------------------------------------------------------------------

//  write out text
int App::Txt(int x, int y, bool draw)
{
	//if (!window)  return;
	text.setString(s);
	text.setStyle(bold ? sf::Text::Bold : sf::Text::Regular);
	text.setColor(clr);
	text.setPosition(x, y);
	if (draw)  pWindow->draw(text);
	return text.getLocalBounds().width;  // advance x pos
}

//  clear rect
void App::Rect(int x, int y,  int sx, int sy, const SClr& c)
{
	//if (!pBackgr)  return;
	pBackgr->setScale(sx-x, sy-y);
	pBackgr->setPosition(x, y);
	pBackgr->setColor(sf::Color(c.r, c.g, c.b));
	pWindow->draw(*pBackgr);
}
void App::Rect(int x, int y,  int sx, int sy,
		  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
	//if (!pBackgr)  return;
	pBackgr->setScale(sx-x, sy-y);
	pBackgr->setPosition(x, y);
	pBackgr->setColor(sf::Color(b, g, r));
	pWindow->draw(*pBackgr);
}

//  frame rect, inefficient
void App::Frame(int x, int y,  int sx, int sy,  int d,
		  const SClr& c)
{
	Rect(x,   y,    sx-d, y+d,  c);
	Rect(x,   sy-d, sx-d, sy,   c);
	Rect(x,   y,    x+d,  sy-d, c);
	Rect(sx-d,y,    sx,   sy,   c);
}

void App::Frame(int x, int y,  int sx, int sy,  int d,
		  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
	Rect(x,   y,    sx-d, y+d,  r, g, b);
	Rect(x,   sy-d, sx-d, sy,   r, g, b);
	Rect(x,   y,    x+d,  sy-d, r, g, b);
	Rect(sx-d,y,    sx,   sy,   r, g, b);
}
