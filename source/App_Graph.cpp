#include "App.h"
#include "Util.h"
#include <cstring>


//  Graphics draw  list
///-----------------------------------------------------------------------------
void App::Graph()
{
	if (li.pat.empty())  return;

	//  patterns  -----
	const int  /// params
		xa = iFontH*2/3,  // add x, margin
		ya = iFontH + iLineH,
		xMax = xs,  // area
		yMax = ye;// - ya;

	//  frame  _|
	Rect(xMax-1,0, xMax+1,yMax, 60,40,20);
//	Rect(0,yMax-1, xMax,yMax+1, 60,40,20);

	//  vars
	int x = 0, y = 0, xw = 0;
	int i, ii = li.pat.size();
	sf::Color cCur;

	li.Update(xMax, xa, ya);  // update

	//for (int j=i; j>=0; --j)
	if (line < 0)  line = 0;
	if (line >= li.lines.size())
		line = li.lines.size()-1;
	i = li.lines[line];
	const Pat& p0 = li.pat[i];

	//  list  -----
	while (i < ii)
	{
		const Pat& p = li.pat[i];
		Clr(p.c);

		//  name
		s = p.s;  // patterns

		x = p.x;  y = p.y - p0.y;  xw = x + p.xw;
		if (y + ya > yMax)  break;

		//  cursor
		if (i == iCur)  // current
		{	Frame(x, y, xw, y+ya, 1, p.c);
			cCur = clr;
		}
		else  // mouse over
		if (xm >= x && xm < xw && ym >= y && ym < y+ya)
		{
			Frame(x, y, xw, y+ya, 2, p.c);
			iPick = i;
			if (mb)
			{	iCur = i;  // button pick, set gui
				strcpy(ed.pat, p.s.c_str());
				ed.r = p.c.r;
				ed.g = p.c.g;
				ed.b = p.c.b;
			}
		}
		Txt(x, y);  // write
		++i;
	}
}
