#include "App.h"
#include "Util.h"


//  Graphics draw
///-----------------------------------------------------------------------------
void App::Graph()
{
	//  clear screen
	//Rect(0,0, xe,ye, 0,0,0);

	//  patterns  -----
	int x = 0, xw = 0, y = 0;
	const int  /// params
		ya = iFontH + 2, xa = 10,  // margins
		xMax = xe/2, yMax = ye - 2*iFontH;  // area
	int i = lOfs, ii = li.pat.size();

	sf::Color c(0,0,0), cCur;
	while (i < ii && y+ya < yMax)
	{
		const Pat& p = li.pat[i];
		Clr(p.r, p.g, p.b);

		//  advance
		if (c == clr && x < xMax)
			x += xw;  // same line
		else  // next line
		{	x = 0;  y += ya;  }
		c = clr;

		//  name
		s = "";
		//s += i2s(p.r)+" "+i2s(p.g)+" "+i2s(p.b)+"  ";
		s += p.s;  // patterns

		xw = Text(x, y, false) + xa;  // get width

		//  cursor
		if (i == lCur)  // current
		{	Frame(x, y, x+xw, y+ya, 1, p.b, p.g, p.r);
			cCur = clr;
		}
		else  // mouse over
		if (xm >= x && xm < x+xw && ym >= y && ym < y+ya)
		{
			Frame(x, y, x+xw, y+ya, 2, p.b, p.g, p.r);
			lPick = i;
			if (mb)  lCur = i;  // button pick
		}

		Text(x, y);  // write
		++i;
	}

	//  current info  -----
	x = xMax+10;  y = 10;  xw = 32;  int yw = iFontH + 10;
	Rect(x, y, x+xw, y+xw, cCur.b, cCur.g, cCur.r);
	y += yw + 20;
	Clr(180,120,120);  s = "R: " + i2s(cCur.r);  Text(x, y);  y += yw;
	Clr(120,180,120);  s = "G: " + i2s(cCur.g);  Text(x, y);  y += yw;
	Clr( 60,150,210);  s = "B: " + i2s(cCur.b);  Text(x, y);  y += yw;

	//  status  -----
	Clr(185,225,255);
	s = "Patterns: " + i2s(li.pat.size()) +
		"  Colors: " + i2s(li.clr.size());
	Text(0, ye - iFontH);

	//  debug  -----
	//return;
	Clr(100,150,200);
	s = "xm: " + i2s(xm) + " ym: " + i2s(ym) + " mb: " + i2s(mb);
	Text(xe - 300, ye - iFontH);
}
