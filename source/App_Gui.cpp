#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
#include "Util.h"
using namespace std;  using namespace ImGui;  using namespace SFML;


#if 0
void RGBtoHSV(int r, int g, int b,  int& h, int& s, int& v)
{
	float fh, fs, fv;
	ColorConvertRGBtoHSV(r/255.f, g/255.f, b/255.f, fh, fs, fv);
	h = fh*255.f;  s = fs*255.f;  v = fv*255.f;
}
void HSVtoRGB(int h, int s, int v,  int& r, int& g, int& b)
{
	float fr, fg, fb;
	ColorConvertHSVtoRGB(h/255.f, s/255.f, v/255.f, fr, fg, fb);
	r = fr*255.f;  g = fg*255.f;  b = fb*255.f;
}
#endif


//  Gui draw and process
///-----------------------------------------------------------------------------
void App::Gui()
{
	const static bool Debug = 0;  //1
	const int yDbg = Debug ? 200 : 100;  // par
	sp = (yWindow - 600.f) / 600.f;  if (sp < 0.f)  sp = 0.f;


	//  controls  wnd  =====
	SetNextWindowPos( ImVec2(0, 10),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(xSplit, yWindow-yDbg-10), ImGuiSetCond_Always);

	bool e, open = true;
	const int wfl = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
	Begin("Controls", &open, wfl);

	//  tabs
	TabLabels(Tab_ALL, tabNames, tab, true);
	Sep(15);  Line(cl0);  Sep(10);


	//  unfocus gui,  keys for list
	if (tab == Tab_List || bHelp)
	{	sf::Event e;
		e.type = sf::Event::MouseButtonPressed;
		e.mouseButton.button = sf::Mouse::Left;
		e.mouseButton.x = 0;  e.mouseButton.y = 0;
		ProcessEvent(e);
		e.type = sf::Event::MouseButtonReleased;
		ProcessEvent(e);
	}

	switch (tab)
	{
	case Tab_List:
	case Tab_Edit:
	{
		//  Properties title
		//---------------------------------------------
		Text("Properties");  Sep(10);

		Pat* p = nullptr;  // current, for edit, set
		if (iCur >= 0 && iCur < li.pat.size())
			p = &li.pat[iCur];

		//  pattern edit  __
		if (edFocus)  // after F2
		{	edFocus = false;  SetKeyboardFocusHere();
		}
		PushItemWidth(140);
		e = InputText("Pattern", ed.pat, sizeof(ed.pat));
		if (e && p)  p->s = ed.pat;  // set
		PopItemWidth();
		Sep(10);

		//  color rect  [ ]
		ImDrawList* dl = GetWindowDrawList();
		const ImVec2 q = GetCursorScreenPos();
		float x = q.x, y = q.y, z=40, sz=z+10;
		ImColor c(ed.r, ed.g, ed.b);
		dl->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x+z, y+z), c,c,c,c);
		Dummy(ImVec2(sz, sz));  SameLine(sz+10, 20);  Text("\nColor  %02X%02X%02X",ed.r,ed.g,ed.b);  // hex clr

		//  r,g,b sliders  ==
		PushItemWidth(-60);  //PushAllowKeyboardFocus(false);
		e = false;
		e |= SliderInt("R", &ed.r, 0, 255, "");  SameLine();  Text(("R  "+i2s(ed.r)).c_str());  // set
		e |= SliderInt("G", &ed.g, 0, 255, "");  SameLine();  Text(("G  "+i2s(ed.g)).c_str());
		e |= SliderInt("B", &ed.b, 0, 255, "");  SameLine();  Text(("B  "+i2s(ed.b)).c_str());
		if (e && p)  SetClr();

		//  h,s,v sliders  todo floats..
		#if 0
		Sep(10);
		bool eh, es, ev;
		//RGBtoHSV(ed.r, ed.g, ed.b, ih, is, iv);
		eh = SliderFloat("H", &ed.h, 0.f, 1.f, "");  SameLine();  Text(("H "+f2s(ed.h,3)).c_str());
		es = SliderFloat("S", &ed.s, 0.f, 1.f, "");  SameLine();  Text(("S "+f2s(ed.s,3)).c_str());
		ev = SliderFloat("V", &ed.v, 0.f, 1.f, "");  SameLine();  Text(("V "+f2s(ed.v,3)).c_str());
		/*if (p && (eh || es || ev))
		{
			int r, g, b;  HSVtoRGB(ih, is, iv, r, g, b);
			p->c.r = ed.r = r;  p->c.g = ed.g = g;  p->c.b = ed.b = b;
		}/**/
		#endif

		//  checks  ...
		Sep(10);
		e = Checkbox("Dir",  &ed.dir);  if (e && p)  UpdDir(*p);
		//e = Checkbox("Link", &ed.lnk);  if (e && p)  p->lnk = ed.lnk;  SameLine();
		//e = Checkbox("Exe",  &ed.exe);  if (e && p)  p->exe = ed.exe;  //SameLine();

		//  attrib  own, or from checks
		SameLine(130);  //Sep(5);
		PushItemWidth(80);
		e = InputText("Attributes", ed.attr, sizeof(ed.attr));
		if (e && p)  p->attr = ed.attr;  // set
		PopItemWidth();

		//  hide, group
		Sep(10);
		e = Checkbox("Hidden",  &ed.hide);  if (e && p)  p->hide = ed.hide;
		SameLine(130);
		e = Checkbox("Group",  &ed.group);  if (e && p)  p->group = ed.group;

		//  group  todo sort
		/*Sep(20);
		PushItemWidth(80);
		e = DragInt("Group", &ed.grp, 0.1f);  ed.grp = std::min(10, std::max(-10, ed.grp));
		if (e && p)  p->grp = ed.grp;  // set
		//e = SliderInt("Group", &ed.grp, -120, 120, "");  SameLine();  Text(i2s(ed.grp).c_str());  if (e && p)  p->grp = ed.grp;  // set
		PopItemWidth();/**/


		//  quick tools
		//---------------------------------------------
		Sep(10);  Line(cl0);  Sep(10);
		e = TreeNode("Search");  // hidden
		if (sFind[0]) {  SameLine(140);  Text("Found: %d  visible: %d", iFoundAll, iFound);  }
		if (e)
		{	Sep(3);
			e = false;
			e |= Checkbox("Case", &findCase);  SameLine();
			e |= Checkbox("Whole", &findWhole);  SameLine();
			e |= Checkbox("Inverse", &findInverse);  if (e)  DoFind();
			TreePop();
		}
		Sep(5);

		PushItemWidth(180);
		if (findFocus)  // after alt-F
		{	findFocus = false;  SetKeyboardFocusHere();
		}
		e = InputText("", sFind, sizeof(sFind));  SameLine();  if (e)  DoFind();
		PopItemWidth();
		e = Button("X");  if (e) {  sFind[0]=0;  DoFind();  }

		Sep(20);  Line(cl0);  Sep(10);
		Text("Project");
		Status& st = status;  //  status  ----
		if (!st.txt.empty() && st.cnt < st.end)
		{	SameLine(0, 20);
			TextColored(ImColor::HSV(st.hue, 0.5f, 1.f-float(st.cnt)/st.end),
						st.txt.c_str());
			++st.cnt;
		}
		Sep(5);
		e = Button("F4 Save");    if (e)  Save();  SameLine();
		e = Button("F5 Reload");  if (e)  Load();

		Sep(10);  int i = set.cmbDC;
		e = Combo("cmbDC", &i, "Double Commander\0Total Commander\0\0");  if (e)  set.cmbDC = i;
		Sep(5);
		e = Button("F8 Export");  if (e)  Export();  SameLine();
		e = Button("F9 Import");  if (e)  Import();
		//Sep(5);

		bool mrg = set.merge;  SameLine();
		e = Checkbox("Merging", &mrg);  if (e && p)  set.merge = mrg;

	}	break;


	case Tab_Settings:
	{	//---------------------------------------------
		PushItemWidth(xSplit-100);
		Text("Dimensions");
		Sep(20);
		Text("List Font Height");  int i = set.iFontH;
		e = SliderInt("F", &i, 1, 32, "");  SameLine();  Text(i2s(set.iFontH).c_str());  if (e) {  set.iFontH = i;  IncFont(0);  }
		Text("Gui Font Height (restart)");  i = set.iFontGui;
		e = SliderInt("FG", &i, 8, 22, "");  SameLine();  Text(i2s(set.iFontGui).c_str());  if (e)  set.iFontGui = i;
		Text("Line Y Spacing");  i = set.iLineH;
		e = SliderInt("L", &i, -2, 12, "");  SameLine();  Text(i2s(set.iLineH).c_str());  if (e)  set.iLineH = i;
		Text("Item X Spacing");  float f = set.fXMargin;
		e = SliderFloat("X", &f, 0.1f, 2.f, "");  SameLine();  Text(f2s(set.fXMargin).c_str());  if (e)  set.fXMargin = f;
		Text("Splitter");
		PushItemWidth(170);
		e = InputFloat("S", &set.fSplit, 0.01f, 0.1f, 2);  if (e)  UpdSplit();  //-
		PopItemWidth();
		Sep(20);
		PopItemWidth();

		PushItemWidth(xSplit-40);
		Sep(20);  Line(cl0);  Sep(10);
		Text("Paths");  Sep(20);

		Text("Project file");
		e = InputText("proj", set.pathProj, sizeof(set.pathProj));
		Sep(5);  Text("doublecmd.xml location");
		e = InputText("DCxml", set.pathDCxml, sizeof(set.pathDCxml));
		Sep(5);  Text("Double Commander executable");
		e = InputText("DCexe", set.pathDCexe, sizeof(set.pathDCexe));
		Sep(5);  Text("Total Commander color.ini");
		e = InputText("TCini", set.pathTCini, sizeof(set.pathTCini));
		PopItemWidth();

		Sep(20);
		Text("Settings");
		Sep(10);
		e = Button("Reload");  if (e)  set.Load();  SameLine();
		e = Button("Save");  if (e)  set.Save();
		Sep(5);
		e = Button("Defaults");  if (e)  set.Default();
	}	break;

	}
	End();


	if (bHelp)  Help();


	//  debug  wnd
	//---------------------------------------------
	SetNextWindowPos( ImVec2(0, yWindow-yDbg),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(xSplit, yDbg), ImGuiSetCond_Always);
	Begin("Status", &open, wfl);

	string s =  // info
		"Patterns: " + i2s(li.pat.size()) +
		//"  Colors: " + i2s(li.clr.size()) +
		"   Lines: " + i2s(li.lines.size());
	Text(s.c_str());

	Sep(10);  Line(cl0);  //Sep(5);
	e = Button("Ctrl-F1  Help");  if (e)  bHelp = 1-bHelp;
	Sep(5);


	if (Debug)
	if (TreeNode("Debug"))  // hidden
	{	Sep(3);
		string s;
		s = "Cur: " + i2s(iCur) + "  Line: " + i2s(line);
		Text(s.c_str());
		s = "xs: " + i2s(xSplit) + "  xe: " + i2s(xWindow) + "  ye: " + i2s(yWindow);
		Text(s.c_str());
		s = "xm: " + i2s(xm) + "  ym: " + i2s(ym) + "  mb: " + i2s(mb);
		Text(s.c_str());
		TreePop();
	}
	End();
}
