#include "App.h"
#include "Util.h"
#include <cstring>
using namespace std;


//  Tools, operations
///-----------------------------------------------------------------------------
bool App::Check()
{
	if (li.pat.empty())  return true;
	//  range, just to be sure
	int lMax = static_cast<int>(li.pat.size()) - 1;
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
void App::InvDir()
{
	if (Check())  return;
	ed.dir = !ed.dir;
	Pat& p = li.pat[iCur];
	UpdDir(p);
}
void App::UpdDir(Pat& p)
{
	p.SetDir(ed.dir);
	strcpy(ed.attr, p.attr.c_str());
}

//  hide
void App::InvHide()
{
	if (Check())  return;
	ed.hide = !ed.hide;
	Pat& p = li.pat[iCur];
	p.hide = ed.hide;
}

//  group
void App::InvGroup()
{
	if (Check())  return;
	ed.group = !ed.group;
	Pat& p = li.pat[iCur];
	p.group = ed.group;
}


//  set cursor, set gui from list  * * *
//-----------------------------------------------------------------------------
void App::SetCur(int ic)
{
	if (li.pat.empty())  {  iCur = 0;  return;  }
	iCur = ic;  Check();

	//  set gui  -----
	const Pat& p = li.pat[iCur];
	//  edits
	strcpy(ed.pat, p.s.c_str());
	strcpy(ed.attr, p.attr.c_str());
	//  color
	ed.r = p.c.r;  ed.g = p.c.g;  ed.b = p.c.b;
	//  checks
	ed.dir = p.dir;  ed.hide = p.hide;  ed.group = p.group;
	ed.onlyDC = p.onlyDC;  ed.onlyTC = p.onlyTC;
	ed.grpSet = p.grpSet;
}


//  inc line  ^ v
//-----------------------------------------------------------------------------
void App::IncLine(int d, int end)
{
	if (Check())  return;

	int lc = li.pat[iCur].l;  // cur line
	int o = iCur - li.lines[lc];  // ofs in cur line
	int lsi = li.lines.size()-1;

	int ln = max(0, min(lsi, lc + d));  // new line
	int l  = li.lines[ln];  // new line start
	int le = li.LineLen(ln);  // new line length

	if (o >= le)  o = le-1;

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
		const Pat& p = li.pat[iCur];  // cur pat
		a = li.lines[p.l];  // begin of cur line
		b = li.LineLen(p.l) + a;  // end
	}
	SClr ec(ed.r, ed.g, ed.b);
	for (int i = a; i < b; ++i)
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
//-----------------------------------------------------------------------------
void App::AddPat(bool start, bool end, bool alt)
{
	if (Check())
	{	//  first
		Pat p;  p.s = "new";
		li.pat.push_back(p);
		return;
	}
	Pat p = li.pat[iCur];  p.s = "new";
	if (alt)
		p.c = SClr(255,255,255);  // to split when 1 line

	if (start)
	{	li.pat.insert(li.pat.begin(), p);  ++iCur;  }
	else if (end)
		li.pat.insert(li.pat.end(), p);
	else   // after current
	{	li.pat.insert(li.pat.begin()+iCur+1, p);  ++iCur;  }
}

//  delete current  ---
void App::DelPat()
{
	if (Check())  return;
	li.pat.erase(li.pat.begin()+iCur);
	SetCur(iCur);
}

void App::Erase(int a, int b)
{
	for (int i=b-1; i>=a; --i)
		li.pat.erase(li.pat.begin()+i);
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
		strFind = findCase ? sFind : strlower(sFind);

	int i = 0, ii = li.pat.size();
	while (i < ii)
	{
		Pat& p = li.pat[i];
		bool found = findInverse;

		//  find match __
		if (doFind)
		{	string s = findCase ? p.s : strlower(p.s);  // case sensitive
			if (findWhole ? s == strFind :  // whole string
				s.find(strFind) != string::npos)
			{
				++iFoundAll;
				found = !findInverse;
			}
		}
		p.match = found;
		++i;
	}
	if (findInverse)
		iFoundAll = ii - iFoundAll;
}


//  goto next/prev find occurence
void App::NextFind(int d)
{
	if (Check())  return;
	if (iFoundAll==0)  return;

	int n = 0, nn = abs(d);
	int i = 0, ii = li.pat.size();
	while (i < ii)  // go around list once
	{
		if (d > 0)  ++iCur;  // next/prev
			  else  --iCur;
		if (iCur >= ii)  iCur = 0;
		if (iCur < 0)  iCur = ii-1;
		++i;

		if (li.pat[iCur].match)
		{
			++n;  // next find match
			if (n==nn)  break;  // rr times
		}
	}
}


///  Move  in list
//-----------------------------------------------------------------------------
void App::Move()
{
	//  Move  line
	//---------------------------
	if (iLineSel >= 0)
	{
		vector<Pat> sel;
		int a = iCur, b = iCur+1;

		int l = iLineSel;  // cur line
		a = li.lines[l];  // begin of cur line
		b = li.LineLen(l) + a;  // end

		for (int i=a; i<b; ++i)  // copy sel
			sel.push_back(li.pat[i]);

		//  insert
		int s = sel.size();
		if (shift)
		{
			Erase(a,b);
			for (int i=s-1; i>=0; --i)
				li.pat.push_front(sel[i]);  // begin
		}
		else
		if (ctrl)
		{
			for (int i=0; i<s; ++i)
				li.pat.push_back(sel[i]);  // end
			Erase(a,b);
		}
		else
		if (iPick >= 0)
		{
			int l = li.pat[iPick].l;  // pick pos line
			if (l != iLineSel)  // needs different line
			{
				int ii = li.lines[l];  // line start
				if (l > iLineSel)  // after
					ii += li.LineLen(l);

				if (l < iLineSel)  // before
					Erase(a,b);

				//  insert sel
				for (int i=s-1; i>=0; --i)
					li.pat.insert(li.pat.begin() + ii, sel[i]);

				if (l > iLineSel)  // after
					Erase(a,b);
			}
		}
	}
	//  Move  1
	//---------------------------
	else
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
}
