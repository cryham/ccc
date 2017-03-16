#include "App.h"
#include <cstring>
using namespace std;


//  Tools, operations
///-----------------------------------------------------------------------------
bool App::Check()
{
	if (li.pat.empty())  return true;
	//  range, just to be sure
	int lMax = li.pat.size()-1;
	if (iCur < 0)    {  iCur = 0;     return true;  }
	if (iCur > lMax) {  iCur = lMax;  return true;  }
	return false;
}

void App::Status::Set(std::string sText, float fHue)
{
	txt = sText;  hue = fHue;  cnt = 0;
}

//  copy, set color
void App::CopyClr()
{
	if (Check())  return;
	copyClr = li.pat[iCur].c;

	status.Set("Copy color", 0.6f);
}

void App::PasteClr()
{
	if (Check())  return;
	li.pat[iCur].c = copyClr;

	status.Set("Paste color", 0.6f);
}

//  toggle
/*void App::InvDir()
{
	if (Check())  return;
	li.pat[iCur].dir = li.pat[iCur].dir;
	ed.dir = li.pat[iCur].dir;  // set gui
}/**/


//  set cursor, set gui from list  * * *
void App::SetCur(int ic)
{
	if (li.pat.empty())  {  iCur = 0;  return;  }
	iCur = ic;
	Check();

	//  set gui  -----
	const Pat& p = li.pat[iCur];
	//  edits
	strcpy(ed.pat, p.s.c_str());
	strcpy(ed.attr, p.attr.c_str());
	//  color
	ed.r = p.c.r;  ed.g = p.c.g;  ed.b = p.c.b;
	//  checks
	ed.dir = p.attr.find('d') != string::npos;
	ed.lnk = p.attr.find('l') != string::npos;
	ed.exe = p.attr.find('x') != string::npos;
}


//  inc line  ^ v
void App::IncLine(int d, int end)
{
	if (Check())  return;
	const Pat& p = li.pat[iCur];
	int o = iCur - li.lines[p.l];  // ofs in cur line
	int ls = li.lines.size()-1;
	int l  = li.lines[std::max(0, std::min(ls, p.l+d))];
//	int le = li.lines[std::max(0, std::min(ls, p.l+d+1))] - l;
//	if (o > le)  o = le;
	if (end==0)
		SetCur(l + o);
	else	// home or end
		SetCur(end < 0 ? l : l-1);
}

//  set colors in line
void App::SetClr(bool line)
{
	int a = iCur, b = iCur+1;
	if (line)
	{
		const Pat& p = li.pat[iCur];
		a = li.lines[p.l];  // begin of cur line
		int ls = li.lines.size()-1, l1 = p.l+1;
		b = l1 <= ls ? li.lines[l1] : li.pat.size();  // end of cur line
	}
	SClr ec(ed.r, ed.g, ed.b);
	for (int i=a; i<b; ++i)
		li.pat[i].c = ec;
}


//  home, end
void App::First(bool ctrl)
{
	if (Check())  return;
	if (ctrl || li.lines.size()==1)
	{	iCur = 0;  return;  }
	IncLine(0,-1);
}
void App::Last(bool ctrl)
{
	if (Check())  return;
	if (ctrl || li.lines.size()==1)
	{	iCur = li.pat.size()-1;  return;  }
	IncLine(1, 1);
}


//  add new  +++
void App::AddPat(bool start, bool end)
{
	if (Check())
	{	//  first
		Pat p;  p.s = "new";
		li.pat.push_back(p);
		return;
	}
	Pat p = li.pat[iCur];  p.s = "new";
	if (start)
		li.pat.insert(li.pat.begin(), p);
	if (end)
		li.pat.insert(li.pat.end(), p);
	else   // after current
		li.pat.insert(li.pat.begin()+iCur+1, p);
}

//  delete current  ---
void App::DelPat()
{
	if (Check())  return;
	li.pat.erase(li.pat.begin()+iCur);
	SetCur(iCur);
}
