#include "App.h"
#include <cstring>


//  Tools, operations
///-----------------------------------------------------------------------------

//  copy, set color
void App::CopyClr()
{
	if (li.pat.empty())  return;
	cpy = li.pat[iCur].c;
	txtStatus = "Copy color";
	hueStatus = 0.6f;
	iStatus = 0;
}

void App::SetClr()
{
	if (li.pat.empty())  return;
	li.pat[iCur].c = cpy;
	txtStatus = "Set color";
	hueStatus = 0.6f;
	iStatus = 0;
}

//  toggle
void App::InvDir()
{
	if (li.pat.empty())  return;
	li.pat[iCur].dir = li.pat[iCur].dir;
}

//  set cursor, set gui from list
void App::SetCur(int ic)
{
	iCur = ic;
	//  range
	int lMax = li.pat.size()-1;
	if (iCur < 0)  iCur = 0;
	if (iCur > lMax)  iCur = lMax;

	//  set gui edit values
	const Pat& p = li.pat[iCur];
	strcpy(ed.pat, p.s.c_str());
	strcpy(ed.attr, p.attr.c_str());
	ed.r = p.c.r;  ed.g = p.c.g;  ed.b = p.c.b;
}

//  inc line
void App::IncLine(int d)
{
	const Pat& p = li.pat[iCur];
	int o = iCur - li.lines[p.l];  // ofs in cur line
	int ls = li.lines.size()-1;
	int l  = li.lines[std::max(0, std::min(ls, p.l+d))];
//	int le = li.lines[std::max(0, std::min(ls, p.l+d+1))] - l;
//	if (o > le)  o = le;
	SetCur(l + o);
}

//  add, del
void App::AddPat(bool start, bool end)
{
	Pat p = li.pat[iCur];  p.s = "new";
	if (start)
		li.pat.insert(li.pat.begin(), p);
	if (end)
		li.pat.insert(li.pat.end()-1, p);
	else   // after current
		li.pat.insert(li.pat.begin()+iCur+1, p);
}

void App::DelPat()
{

}
