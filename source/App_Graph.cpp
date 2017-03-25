#include "App.h"
#include "Util.h"
using namespace std;


//  Graphics draw  list
///-----------------------------------------------------------------------------
void App::Graph()
{

	///  dim params  ----------
	const int
		xa = set.iFontH * set.fXMargin,  // add x  with margin
		ya = set.iFontH + set.iLineH,    // line height
		xMin = xSplit + 10, xMax = xWindow,  // area
		yMax = yWindow,
		yf2 = set.iFontH/2,
		xBack = std::min(xMax - 30.f,  // group row length
			xMin + xa * 50 * set.fXBackGroup);

	//  animate find color
	time += dt;
	float a = 255.f * (0.75f + 0.25f * cosf(12.f * time));
	const SClr findRect(a, 255, a);

	const static SClr  ///  colors
		findBack(25,25,35),
		curBack(40,40,60),
		sldBack(40,40,60), sldView(80,80,140), sldOver(120,120,180),
		sldSel(170,170,200), sldPick(170,170,255), sldPos(200,200,240),
		moveMark(215,255,255), clrGroup(40,40,50);


	//  drag | splitter
	bool overSld = !alt && xm > xBack;  // over slider
	bool overSpl = !alt && xm > xSplit-4 && xm < xSplit+2;

	if (overSpl && mb == 1 && !mbo)
		dragSplit = true;
	if (dragSplit)
	{
		xSplit = std::max(150, std::min(xWindow - 200, xm));
		set.fSplit = float(xSplit) / xWindow;
		UpdSplit();
		if (mb == 0)
			dragSplit = false;
	}
	Rect(xSplit-2, 0, xSplit+2, yMax,
		dragSplit || overSpl ? sldView : sldBack);


	//  update list pos  //todo: not every frame..
	li.Update(xMin, xMax, xa, ya);

	const int
		ll = li.lines.size();

	if (line < 0)  line = 0;
	if (line >= ll)  line = ll-1;

	const int
		ii = li.pat.size(),
		i1 = li.lines[line],
		y0 = li.pat[i1].y;

	//  vars
	int x, y, xw, yc, yy, yh;
	int i = i1;

	iFound = 0;  iPick = -1;


	//  List  --------------------------------------------------------
	while (i < ii)
	{
		const Pat& p = li.pat[i];
		Clr(p.c);

		//  name
		str = p.s;  // pattern

		//  pos
		x = p.x;  y = p.y - y0;  xw = x + p.xw;
		if (y + ya > yMax)
			break;  // outside

		yc = y+2;  yy = yc+ya+2;  // cur
		yh = yc + yf2;


		//  group  row backgr  ==
		if (p.group)
			Rect(x, yc+2, xBack, yy-1, clrGroup);

		//  find __
		if (p.match && !bHelp)
			Rect(x, yc+2, xw, yy-1, findBack);

		//  current []
		if (i == iCur)
			Rect(x, yc+2, xw, yy-1, curBack);


		///  Text write
		Txt(x, y);

		//  hidden strikeout--
		if (!p.Visible())
			Rect(x, yh, xw-xa, yh+1, p.c);


		//  selected line  ==
		if (p.l == iLineSel && iLineSel >= 0)
			Frame(x, yc, xw, yy, 1, 0,0, p.c);

		//  current []
		if (i == iCur)
			Frame(x, yc, xw, yy, 1, p.c);

		//  mouse over [ ]
		if (tab == Tab_List &&
			!bHelp && !dragSplit && !dragSlider)  //+
		if (xm >= x && xm < xw &&
			ym >= y && ym < y+ya)
		{
			if (i != iCur)
				Frame(x, yc, xw, yy, 2, p.c);

			iPick = i;  // pick, move marker

			if (!alt)
			if (mb == 1)  // LMB
			{	SetCur(i);  // mouse pick 1
				iLineSel = -1;  // unselect line
			}else
			if (mb == 2)  // RMB
			{	SetCur(i);  // for color edit
				iLineSel = i < 0 ? -1 : p.l;  // select line
		}	}

		//  find match  underline __
		if (p.match && !bHelp)
		{	++iFound;  // visible only
			Rect(x, yy-1, xw, yy, findRect);
		}
		++i;
	}


	//  Slider  |  pos, view size
	//---------------------------------------------------------------

	if (overSld && !dragSplit)
	//if (!alt && iPick == -1)  // drag anywhere-
		if (mb == 1 && !mbo)
		{	ymo = ym;  lno = line;  dragSlider = true;  }

	if (dragSlider)
	{	/**/
		while (ym - ymo > ya)
		{	ymo += ya;  line += 4;  }  //par-
		while (ym - ymo < ya)
		{	ymo -= ya;  line -= 4;  }/**/
		//line = float(ym) / yMax * (ll-1);
		//line = oline + (ym - ymo) / ya;
			// * float(ym) / yMax * (ll-1);
	}
	if (mb == 0)
		dragSlider = false;

	//  draw slider
	if (ii > 5 || ll > 1)  // hide if not much
	{
		#define Y(y)  float(y) / ii * yMax
		int y1 = Y(i1), y2 = Y(i),
			p1 = Y(iCur), p2 = Y(iCur+1);
		if (p2 == p1)  ++p2;  // mix 1 pix
		const int x0 = xMax - 20;  //par

		Rect(x0, 0, xMax, yMax, sldBack);  // background
		Rect(x0, y1, xMax, y2, sldView);  // visible area
		if (overSld)
			Frame(x0, y1, xMax, y2, 1, sldOver);

		if (iLineSel >= 0 &&  // selected line
			iLineSel < ll)
		{
			int a = li.lines[iLineSel];  // begin of sel line
			int b = li.LineLen(iLineSel) + a;  // end
			y1 = Y(a);  y2 = Y(b);
			Rect(x0, y1, xMax, y2, sldSel);
		}

		Rect(x0, p1, xMax, p2, sldPos);  // cursor
		if (iPick >= 0)  // pick.
		{	p1 = Y(iPick);  p2 = Y(iPick+1);  if (p2==p1)  ++p2;
			Rect(x0+4, p1, xMax-4, p2, sldPick);  // pick
		}

		//  all find matches on slider
		for (i=0; i < ii; ++i)
		{
			y1 = Y(i);  y2 = y1+1;
			if (li.pat[i].match)
				Rect(xMax-8, y1, xMax, y2, findRect);
			//if (li.pat[i].sel)
			//	Rect(x0, y1, x0+8, y2, findRect);
		}
		#undef Y
	}


	//  move marker
	//--------------------
	if (alt)
	{	int x = iLineSel < 0 ? 40 : 90;  // long if line

		if (shift)  // begin
			Rect(xMin, 0, xMin+x, 2, moveMark);
		else
		if (ctrl)  // end
			Rect(xMin, yMax-2, xMin+x, yMax, moveMark);
	}

	///  Move  alt-LMB
	///-------------------
	if (alt && mb == 1 && !mbo)
		Move();

	mbo = mb;
}
