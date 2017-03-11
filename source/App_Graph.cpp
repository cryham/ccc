#include "App.h"
#include "Util.h"
#include <cstring>


//  Graphics draw
///-----------------------------------------------------------------------------
void App::Graph()
{
	//  clear screen
	//Rect(0,0, xe,ye, 0,0,0);

	//  patterns  -----
	const int  /// params
		xa = iFontH*2/3,  // add x, margin
		ya = iFontH + 2,  // bottom margin
		xMax = xs,  // area
		yMax = ye - ya;

	//  frame  _|
	Rect(xMax-1,0, xMax+1,yMax, 60,40,20);
	Rect(0,yMax-1, xMax,yMax+1, 60,40,20);

	//  vars
	int x = 0, y = 0, xw = 0;
	int i = lOfs, ii = li.pat.size();
	sf::Color cCur;

	li.Update(xMax, xa, ya);  // update

	//for (int j=i; j>=0; --j)

	while (i < ii)
	{
		const Pat& p = li.pat[i];
		Clr(p.c);

		//  name
		s = p.s;  // patterns

		x = p.x;  y = p.y;  xw = p.xw;
		if (p.y + ya > yMax)  break;

		//  cursor
		if (i == lCur)  // current
		{	Frame(x, y, x+xw, y+ya, 1, p.c);
			cCur = clr;
		}
		else  // mouse over
		if (xm >= x && xm < x+xw && ym >= y && ym < y+ya)
		{
			Frame(x, y, x+xw, y+ya, 2, p.c);
			lPick = i;
			if (mb)
			{	lCur = i;  // button pick, set gui
				strcpy(pat, p.s.c_str());
				r = p.c.r;
				g = p.c.g;
				b = p.c.b;
			}
		}

		Txt(x, y);  // write
		++i;
	}
	return;

	//  current info  -----
	x = xMax+100;  y = 500;  xw = 32;  int yw = iFontH + 10;
	Rect(x, y, x+xw, y+xw, cCur.b, cCur.g, cCur.r);
	y += yw + 20;
	Clr(180,120,120);  s = "R: " + i2s(cCur.r);  Txt(x, y);  y += yw;
	Clr(120,180,120);  s = "G: " + i2s(cCur.g);  Txt(x, y);  y += yw;
	Clr( 60,150,210);  s = "B: " + i2s(cCur.b);  Txt(x, y);  y += yw;

	//  status  -----
	Clr(185,225,255);
	s = "Patterns: " + i2s(li.pat.size()) +
		"  Colors: " + i2s(li.clr.size());
	Txt(0, ye - iFontH);

	//  debug  -----
	//return;
	Clr(100,150,200);
	s = "xs: " + i2s(xs) + " xe: " + i2s(xe) + " ye: " + i2s(ye);
	Txt(xe - 300, ye - 2*iFontH);
	s = "xm: " + i2s(xm) + " ym: " + i2s(ym) + " mb: " + i2s(mb);
	Txt(xe - 300, ye - iFontH);
}
