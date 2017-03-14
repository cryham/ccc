#include "App.h"
#include "Util.h"
#include <string.h>
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
	#if 0  // left
		xMin = 0, xMax = xSplit,  // area
	#else  // right
		xMin = xSplit+10, xMax = xWindow,  // area
	#endif
		yMax = yWindow;// - ya;

	//  frame  _|
	Rect(xMax-1,0, xMax+1,yMax, 60,40,20);
	//Rect(0,yMax-1, xMax,yMax+1, 60,40,20);

	//  update
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
	int iPick = -1;
	const static SClr mrk(215,255,255);

	//  list  ----------
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

		if (i == iCur)  // current
		{
			Frame(x, yc, xw, yy, 1, p.c);
		}
		else  // mouse over []
		if (!bHelp && tab == Tab_List)  //+
		if (xm >= x && xm < xw && ym >= y && ym < y+ya)
		{
			Frame(x, yc, xw, yy, 2, p.c);

			if (alt && !shift && !ctrl)
				iPick = i;  // move marker |

			if (mb && !alt)
				SetCur(i);  // mouse pick
		}

		//  find match __
		if (p.match &&!bHelp)
		{	++iFound;  // visible only
			Rect(x, yy-1, xw, yy, 255,255,255);
		}
		++i;
	}

	//  slider |  pos, view size  -----
	const SClr sldBack(40,40,60), sldView(80,80,140), sldPos(230,230,255);
	#define Y(y)  float(y) / ii * yMax
	int y1 = Y(i1), y2 = Y(i),
		p1 = Y(iCur), p2 = Y(iCur+1);  if (p2==p1)  ++p2;
	const int x0 = xMax-15;
	Rect(x0, 0, xMax, yMax, sldBack);
	Rect(x0, y1, xMax, y2, sldView);  // visible area
	Rect(x0, p1, xMax, p2, sldPos);  // cursor


	if (alt)  // move marker -
	if (shift)  // begin
		Rect(xMin, 0, xMin+20, 2, mrk);
	else
	if (ctrl)  // end
		Rect(xMin, yMax-2, xMin+20, yMax, mrk);

	//  move  []<-
	if (alt && mb && !mbo)
	if (shift || ctrl || iPick >= 0)
	{
		//  common
		Pat p = li.pat[iCur];  // cur copy
		li.pat.erase(li.pat.begin()+iCur);  // del

		if (shift)
			li.pat.push_front(p);  // begin
		else if (ctrl)
			li.pat.push_back(p);  // end
		else
			li.pat.insert(li.pat.begin() + iPick, p);  // pick pos
	}
	mbo = mb;
}


//  Find
//-----------------------------------------------------------------------------
void App::DoFind()
{
	//  find vars
	iFoundAll = 0;
	bool doFind = sFind[0] != 0;
	string strFind;
	if (doFind)
		strFind = strlower(sFind);

	int i = 0, ii = li.pat.size();
	while (i < ii)
	{
		Pat& p = li.pat[i];
		bool found = false;

		//  find match __
		if (doFind)
		//if (p.s.find(sFind) != string::npos)  // case sens
		if (strlower(p.s).find(strFind) != string::npos)  // case insens
		{
			++iFoundAll;
			found = true;
		}
		p.match = found;
		++i;
	}
}
