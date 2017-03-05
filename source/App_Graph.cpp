#include "App.h"


//  Graphics draw
///-----------------------------------------------------------------------------
void App::Graph()
{
	//  clear screen
	Rect(0,0, xe,ye, 0,0,0);

	//  patterns list
	int x = 0, y = 0, yy = ye - 2*iFontH;
	size_t i = lOfs, ii = li.pat.size();

	while (i < ii && y < yy)
	{
		const Pat& p = li.pat[i];
		Clr(p.r, p.g, p.b);  //Clr(185,225,255);
		s = i2s(p.r)+" "+i2s(p.g)+" "+i2s(p.b)+"  ";
		s += p.s;  // patterns

		x += Text(x, y);

		x = 0;  y += iFontH;  // next line
		++i;
	}

	//  status list
	Clr(185,225,255);
	s = "Patterns: " + i2s(li.pat.size());
		//"  Colors: " + i2s(li.clr.size());
	Text(0, ye - iFontH);

	//  debug
	Clr(100,125,150);
	s = "xm: " + i2s(xm) + " ym: " + i2s(ym);
	Text(xe - 300, ye - iFontH);
}
