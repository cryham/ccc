#include <math.h>
#include "App.h"
#include "Util.h"
using namespace std;


//  Graphics draw  list
///-----------------------------------------------------------------------------
void App::Graph()
{
	//  clear
	pWindow->clear(sf::Color(set.cb, set.cg, set.cr));


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
	bool ok = !alt && !bHelp;
	bool overSld = ok && xm > xBack;  // over slider
	bool overSpl = ok && xm > xSplit-4 && xm < xSplit+2;

	if (overSpl && mb == 1 && !mbo)
		dragSplit = true;
	if (dragSplit)
	{
		xSplit = max(150, min(int(xWindow) - 200, xm));
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
		ii = li.pat.size(), ll = li.lines.size();

	if (line < 0)   line = 0;
	if (line >= ll) line = ll-1;

	const int
		i1 = li.lines[line],
		y1 = li.pat[i1].y,  lc = li.pat[iCur].l;

	//  vars
	int x, y, xw, yc, yy, yh;
	int i = i1, llast = line;

	iFound = 0;  iPick = -1;


	//  List  --------------------------------------------------------
	while (i < ii)
	{
		const Pat& p = li.pat[i];
		if (p.show)  // visible
		{
			Clr(p.c);

			//  name
			str = p.s;  // pattern

			//  pos
			x = p.x;  y = p.y - y1;  xw = x + p.xw;
			if (y + ya > yMax)
				break;  // outside

			yc = y+2;  yy = yc+ya+2;  // cur
			yh = yc + yf2;

			//  group set id
			if (p.group && p.grpSet > 0)
			{
				str += "  [" + i2s(p.grpSet) + "]";
				xw += 30;
			}

			//  group  row backgr  ==
			if (p.group)
				Rect(x, yc+2, xBack, yy-1,
					 HSVtoRGB(p.grpSet*0.2f+0.7f, 0.4f, 0.2f));

			//  find __
			if (p.match && !bHelp)
				Rect(x, yc+2, xw, yy-1, findBack);

			//  current []
			if (i == iCur)
				Rect(x, yc+2, xw, yy-1, curBack);


			///  Text write
			Txt(x, y);

			//  hidden strikeout--
			if (p.hide)
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
		}
		++i;  llast = p.l;
	}


	//  Slider  |  pos, view size
	//---------------------------------------------------------------

	if (overSld && !dragSplit)
	//if (!alt && iPick == -1)  // drag anywhere-
		if (mb == 1 && !mbo)
		{	ymo = ym;  lno = line;  dragSlider = true;  }

	#define NEW_SL  // use new slider

	if (dragSlider)
	{
	#ifdef NEW_SL
		line = float(ym) / yMax * (ll-1);
		line = lno + float(ym - ymo) / yMax * (ll-1);
	#else
		while (ym - ymo > ya)
		{	ymo += ya;  line += 4;  }  //par-
		while (ym - ymo < ya)
		{	ymo -= ya;  line -= 4;  }/**/
	#endif
	}
	if (mb == 0)
		dragSlider = false;

	//  draw slider
	if (ii > 5 || ll > 1)  // hide if not much
	{
	#ifdef NEW_SL
		///  New by lines,  coarse, const height

		#define L(l)  float(l) / ll * yMax
		#define y12(a, b) \
			y1 = L(a);  y2 = L(b); \
			if (y2==y1)  ++y2;  // mix 1 pix

		int ln, y1,y2;
		y12(line, llast+1);
		const int x0 = xMax - 20;  //par

		Rect(x0, 0, xMax, yMax, sldBack);  // background
		Rect(x0, y1, xMax, y2, sldView);  // visible area
		if (overSld)
			Frame(x0, y1, xMax, y2, 2, sldOver);

		if (iLineSel >= 0 &&  // selected line
			iLineSel < ll)
		{
			y12(iLineSel, iLineSel+1);
			Rect(x0, y1, xMax, y2, sldSel);
		}

		y12(lc, lc+1);  // cursor
		Rect(x0, y1, xMax, y2, sldPos);  // cursor

		if (iPick >= 0)  // pick.
		{	ln = li.pat[iPick].l;
			y12(ln, ln+1);
			Rect(x0+4, y1, xMax-4, y2, sldPick);  // pick
		}

		//  all find matches on slider
		for (i=0; i < ii; ++i)
		if (li.pat[i].match)
		{
			y12(li.pat[i].l, li.pat[i].l+1);//  y2 = y1+1;
			Rect(xMax-8, y1, xMax, y2, findRect);
			//if (li.pat[i].sel)
			//	Rect(x0, y1, x0+8, y2, findRect);
		}
		#undef y12
		#undef L
	#else
		///  Old by id,  detailed, variable height

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
	#endif
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
