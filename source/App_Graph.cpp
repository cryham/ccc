#include "App.h"
#include "Util.h"
using namespace std;


//  Graphics draw  list
///-----------------------------------------------------------------------------
void App::Graph()
{
	if (li.pat.empty())  return;

	///  dim params  -----
	const int
		xa = set.iFontH * set.fXMargin,  // add x, margin
		ya = set.iFontH + set.iLineH,  // line height
		xMin = xSplit+10, xMax = xWindow,  // area
		yMax = yWindow;

	//  frame  _|
	//Rect(xMax-1,0, xMax+1,yMax, 60,40,20);
	//Rect(0,yMax-1, xMax,yMax+1, 60,40,20);

	//  update  //todo: not every frame..
	li.Update(xMin, xMax, xa, ya);

	if (line < 0)  line = 0;
	if (line >= li.lines.size())
		line = li.lines.size()-1;

	//  vars
	int x = 0, y = 0, xw = 0;
	int i = li.lines[line], ii = li.pat.size();
	int i1 = i, yc, yy;
	const Pat& p0 = li.pat[i];

	iFound = 0;
	iPick = -1;
	const static SClr mrk(215,255,255);


	//  List  --------------
	while (i < ii)
	{
		const Pat& p = li.pat[i];
		Clr(p.c);

		//  name
		str = p.s;  // pattern

		x = p.x;  y = p.y - p0.y;  xw = x + p.xw;
		if (y + ya > yMax)  break;

		Txt(x, y);  // write

		//  cursor []  -----
		yc = y+2;  yy = yc+ya;


		if (p.l == iLineSel && iLineSel >= 0)  // selected line
		{
			Frame(x, yc, xw, yy, 1, p.c);
		}
		if (i == iCur && iLineSel < 0)  // current
		{
			Frame(x, yc, xw, yy, 1, p.c);
		}
		//  mouse over []
		if (tab == Tab_List && !bHelp)  //+
		if (xm >= x && xm < xw && ym >= y && ym < y+ya)
		{
			if (i != iCur)
			Frame(x, yc, xw, yy, 2, p.c);

			if (alt && !shift && !ctrl)
				iPick = i;  // move marker |

			if (!alt)
			if (mb == 1)  // LMB
			{	SetCur(i);  // mouse pick 1
				iLineSel = -1;  // unselect line
			}else
			if (mb == 2)  // RMB
			{	SetCur(i);  // for color edit
				iLineSel = i < 0 ? -1 : p.l;  // select line
		}	}

		//  find match __
		if (p.match && !bHelp)
		{	++iFound;  // visible only
			Rect(x, yy-1, xw, yy, 255,255,255);
		}
		++i;
	}


	//  Slider  |  pos, view size
	//-----------------------------------
	const static SClr sldBack(40,40,60), sldView(80,80,140), sldPos(230,230,255);
	const int x0 = xMax-15;

	#define Y(y)  float(y) / ii * yMax
	int y1 = Y(i1), y2 = Y(i),
		p1 = Y(iCur), p2 = Y(iCur+1);
	if (p2==p1)  ++p2;
	#undef Y

	Rect(x0, 0, xMax, yMax, sldBack);
	Rect(x0, y1, xMax, y2, sldView);  // visible area
	Rect(x0, p1, xMax, p2, sldPos);  // cursor


	//  move marker
	//--------------------
	if (alt)
	{	x = iLineSel < 0 ? 40 : 90;  // long if line

		if (shift)  // begin
			Rect(xMin, 0, xMin+x, 2, mrk);
		else
		if (ctrl)  // end
			Rect(xMin, yMax-2, xMin+x, yMax, mrk);
	}

	///  Move  alt-LMB
	///-------------------
	if (alt && mb==1 && !mbo)
		Move();

	mbo = mb;
}
