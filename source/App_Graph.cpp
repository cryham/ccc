#include "App.h"
#include "Util.h"


//  Graphics draw  list
///-----------------------------------------------------------------------------
void App::Graph()
{
	if (li.pat.empty())  return;

	///  dim params  -----
	const int
		xa = iFontH*2/3,  // add x, margin
		ya = iFontH + iLineH,
		xMax = xs,  // area
		yMax = ye;// - ya;

	//  frame  _|
	Rect(xMax-1,0, xMax+1,yMax, 60,40,20);
	//Rect(0,yMax-1, xMax,yMax+1, 60,40,20);

	li.Update(xMax, xa, ya);  // update

	//for (int j=i; j>=0; --j)
	if (line < 0)  line = 0;
	if (line >= li.lines.size())
		line = li.lines.size()-1;

	//  vars
	int x = 0, y = 0, xw = 0;
	int i = li.lines[line], ii = li.pat.size();
	int i1 = i, yc;
	const Pat& p0 = li.pat[i];

	//  list  -----
	while (i < ii)
	{
		const Pat& p = li.pat[i];
		Clr(p.c);

		//  name
		str = p.s;  // pattern

		x = p.x;  y = p.y - p0.y;  xw = x + p.xw;
		if (y + ya > yMax)  break;

		//  cursor
		yc = y+2;
		if (i == iCur)  // current
			Frame(x, yc, xw, yc+ya, 1, p.c);
		else  // mouse over
		if (xm >= x && xm < xw && ym >= y && ym < y+ya)
		{
			Frame(x, yc, xw, yc+ya, 2, p.c);
			//iPick = i;
			if (mb)
				SetCur(i);  // button pick
		}
		Txt(x, y);  // write
		++i;
	}

	//  slider  pos, view size  -----
	const SClr sldBack(40,40,60), sldView(80,80,140), sldPos(230,230,255);
	#define Y(y)  float(y) / ii * yMax
	int y1 = Y(i1), y2 = Y(i),
		p1 = Y(iCur), p2 = Y(iCur+1);  if (p2==p1)  ++p2;
	const int xs = 15;
	Rect(xMax-xs, 0, xMax, yMax, sldBack);
	Rect(xMax-xs, y1, xMax, y2, sldView);  // visible area
	Rect(xMax-xs, p1, xMax, p2, sldPos);  // cursor
}
