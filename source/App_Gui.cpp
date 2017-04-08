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
	const int yDbg = Debug ? 210 : 110;  // par
	sp = (yWindow - 600.f) / 600.f;  if (sp < 0.f)  sp = 0.f;


	//  controls  wnd  =====
	SetNextWindowPos( ImVec2(0, 0),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(xSplit, yWindow-yDbg), ImGuiSetCond_Always);

	bool e, open = true;
	const int wfl = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
	Begin("Controls", &open, wfl);

	//  tabs
	Sep(5);
	TabLabels(Tab_ALL, tabNames, tab, true);
	Sep(5);  Line(cl0);  Sep(5);


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

	#define BtnRed()  PushStyleColor(ImGuiCol_Button, ImVec4(0.55f, 0.4f, 0.7f, 0.30f));
	#define BtnNorm()  PopStyleColor();


	switch (tab)
	{
	case Tab_List:
	case Tab_Edit:
	{
		//  Pattern  Properties
		//---------------------------------------------
		Text("Properties");  Sep(5);

		Pat* p = nullptr;  // current, for edit, set
		if (iCur >= 0 && iCur < li.pat.size())
			p = &li.pat[iCur];

		//  pattern edit  __
		if (edFocus)  // after F2
		{	edFocus = false;  SetKeyboardFocusHere();
		}
		if (p && p->group)
		{
			PushItemWidth(200);
			e = InputText("Group name", ed.pat, sizeof(ed.pat));
		}else{
			PushItemWidth(140);
			e = InputText("Pattern", ed.pat, sizeof(ed.pat));
		}
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
		//int h;  SameLine();  RadioButton("RGB",&h);  SameLine();  RadioButton("HSV",&h);

		//  r,g,b sliders  ==
		PushItemWidth(-60);  //PushAllowKeyboardFocus(false);
		e = false;
		e |= SliderInt("R", &ed.r, 0, 255, "");  SameLine();  Text(("R  "+i2s(ed.r)).c_str());
		e |= SliderInt("G", &ed.g, 0, 255, "");  SameLine();  Text(("G  "+i2s(ed.g)).c_str());
		e |= SliderInt("B", &ed.b, 0, 255, "");  SameLine();  Text(("B  "+i2s(ed.b)).c_str());
		if (e && p)  SetClr();  // set

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

		//  attrib  own, or from checks
		SameLine(130);  //Sep(5);
		PushItemWidth(80);
		e = InputText("Attributes", ed.attr, sizeof(ed.attr));  if (e && p)  p->attr = ed.attr;
		PopItemWidth();

		//  hide
		Sep(5);  Text("Advanced");  Sep(5);
		e = Checkbox("Hidden",  &ed.hide);  if (e && p)  p->hide = ed.hide;

		SameLine(130);
		Text("Only for");
		SameLine();  e = Checkbox("DC", &ed.onlyDC);  if (e && p)  p->onlyDC = ed.onlyDC;
		SameLine();  e = Checkbox("TC", &ed.onlyTC);  if (e && p)  p->onlyTC = ed.onlyTC;

		//  group set id
		Sep(5);
		e = Checkbox("Group",  &ed.group);  if (e && p)  p->group = ed.group;

		PushItemWidth(80);
		SameLine(130);
		e = DragInt("Set", &ed.grpSet, 0.04f);
		ed.grpSet = min(li.maxSets-1, max(0, ed.grpSet));
		if (e && p)  p->grpSet = ed.grpSet;
		PopItemWidth();


		//  Find
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

		PushItemWidth(140);
		if (findFocus)  // after alt-F
		{	findFocus = false;  SetKeyboardFocusHere();
		}
		e = InputText("", sFind, sizeof(sFind));  SameLine();  if (e)  DoFind();
		PopItemWidth();
		e = Button("X");  if (e) {  sFind[0]=0;  DoFind();  }
		SameLine(230);  e = Button("<");  if (e)  NextFind(-dFind);
		SameLine(275);  e = Button(">");  if (e)  NextFind( dFind);


		//  Project
		//---------------------------------------------
		Sep(5);  Line(cl0);  Sep(5);
		Text("Visible sets");

		Sep(10);
		for (int i=0; i <= li.curSets; ++i)
		{	int ii = i%5;
			if (ii>0)  SameLine(ii*50+20);

			bool b = li.visSet[i];
			e = Checkbox(i2s(i).c_str(), &b);  if (e)  li.visSet[i] = b;
		}

		Sep(10);  Line(cl0);  Sep(10);
		Text("Project");

		Status& st = status;  //  status  ----
		if (!st.txt.empty() && st.cnt < st.end)
		{	SameLine(0, 20);
			TextColored(ImColor::HSV(st.hue, 0.5f, 1.f-float(st.cnt)/st.end),
						st.txt.c_str());
			++st.cnt;
		}
		Sep(5);
		BtnRed();
		e = Button("F4 Save");    if (e)  Save();  SameLine();
		BtnNorm();
		e = Button("F5 Reload");  if (e)  Load();

		Sep(10);  int i = set.cmbDC;
		PushItemWidth(220);
		e = Combo("cmbDC", &i, "Double Commander\0Total Commander\0\0");  if (e)  set.cmbDC = i;
		PopItemWidth();

		Sep(5);
		BtnRed();
		e = Button("F8 Export");  if (e)  Export();  SameLine();
		BtnNorm();
		e = Button("F9 Import");  if (e)  Import();
		//Sep(5);

		bool mrg = set.merge;  SameLine();
		e = Checkbox("Merging", &mrg);  if (e && p)  set.merge = mrg;

	}	break;


	case Tab_Settings:
	{
		//---------------------------------------------
		e = Button("Defaults");  if (e)  set.Default();  SameLine();
		e = Button("Reload");  if (e)  set.Load();  SameLine();
		BtnRed();
		e = Button("Save");  if (e)  set.Save();
		BtnNorm();
		Sep(20);

		PushItemWidth(xSplit-40);
		Text("Page");  SameLine(80);
		TabLabels(STab_ALL, setTabNames, setTab, true);
		Sep(10);  Line(cl0);  Sep(5);

		const size_t sp = set.PathLen;  // all same size
		int i;  float f;

		switch (setTab)
		{
		case STab_Paths:
			e = Button("Project file ...");  if (e)  Open(set.pathProj);
			InputText("proj", set.pathProj, sp);

			//  DC
			Sep(10);  e = Button("Double Commander - doublecmd.xml ...");  if (e)  Open(set.pathDCxml);
			InputText("DCxml", set.pathDCxml, sp);
			BtnRed();
			Sep(5);  e = Button("Double Commander - executable: ");  if (e)  Open(set.pathDCexe);
			BtnNorm();
			InputText("DCexe", set.pathDCexe, sp);

			//  TC
			Sep(10);  e = Button("Total Commander - color.ini ...");  if (e)  Open(set.pathTCini);
			InputText("TCini", set.pathTCini, sp);
			BtnRed();
			Sep(5);  e = Button("Total Commander - executable: ");  if (e)  Open(set.pathTCexe);
			BtnNorm();
			InputText("TCexe", set.pathTCexe, sp);
			PopItemWidth();
			break;

		case STab_Dims:
			PushItemWidth(xSplit-100);

			Text("List Font Height");  i = set.iFontH;
			e = SliderInt("LFh", &i, 1, 32, "");  SameLine();  Text(i2s(set.iFontH).c_str());  if (e) {  set.iFontH = i;  IncFont(0);  }
			Text("Gui Font Height (restart)");  i = set.iFontGui;
			e = SliderInt("GFh", &i, 8, 22, "");  SameLine();  Text(i2s(set.iFontGui).c_str());  if (e)  set.iFontGui = i;

			Sep(5);
			Text("Line Y Spacing");  i = set.iLineH;
			e = SliderInt("LYs", &i, -3, 8, "");  SameLine();  Text(i2s(set.iLineH).c_str());  if (e)  set.iLineH = i;
			Text("Item X Spacing");  f = set.fXMargin;
			e = SliderFloat("IXs", &f, 0.3f, 2.5f, "");  SameLine();  Text(f2s(set.fXMargin).c_str());  if (e)  set.fXMargin = f;

			Sep(5);
			Text("Group row length");  f = set.fXBackGroup;
			e = SliderFloat("Grl", &f, 0.0f, 1.f, "");  SameLine();  Text(f2s(set.fXBackGroup).c_str());  if (e)  set.fXBackGroup = f;

			Text("Splitter");  PushItemWidth(170);
			e = InputFloat("Spl", &set.fSplit, 0.01f, 0.1f, 2);  if (e)  UpdSplit();
			PopItemWidth();

			PopItemWidth();
			break;

		case STab_Other:
			e = Checkbox("Esc quits",  &set.escQuit);
			Sep(5);
			Text("Background color");
			Sep(5);
			PushItemWidth(xSplit-100);
			i = set.cr;  e = SliderInt("cR", &i, 0, 255, "");  SameLine();  Text(("R  "+i2s(i)).c_str());  if (e)  set.cr = i;
			i = set.cg;  e = SliderInt("cG", &i, 0, 255, "");  SameLine();  Text(("G  "+i2s(i)).c_str());  if (e)  set.cg = i;
			i = set.cb;  e = SliderInt("cB", &i, 0, 255, "");  SameLine();  Text(("B  "+i2s(i)).c_str());  if (e)  set.cb = i;
			PopItemWidth();
			Sep(10);
			break;
		}
	}	break;

	}
	End();


	if (bHelp)  Help();


	//  status, debug  wnd
	//---------------------------------------------
	SetNextWindowPos( ImVec2(0, yWindow-yDbg),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(xSplit, yDbg), ImGuiSetCond_Always);
	Begin("Status", &open, wfl);

	string s =  // info
		//"Fps: " + f2s(1/dt,1,3) + "  "+
		"Patterns: " + i2s(li.pat.size()) +
		"   Colors: " + i2s(li.clr.size()) + "\n"+
		"     Lines: " + i2s(li.lines.size()) + "   Real: " + i2s(li.linesReal);
	Text(s.c_str());

	Sep(10);  Line(cl0);  //Sep(5);
	e = Button("Ctrl-F1  Help");  if (e)  bHelp = 1-bHelp;
	Sep(5);


	if (Debug)
	if (TreeNode("Debug"))  // hidden
	{	Sep(3);
		string s;
		s = "Fps: " + f2s(1/dt,1,3) + "  Cur: " + i2s(iCur) + "  Line: " + i2s(line);
		Text(s.c_str());
		s = "xs: " + i2s(xSplit) + "  xe: " + i2s(xWindow) + "  ye: " + i2s(yWindow);
		Text(s.c_str());
		s = "xm: " + i2s(xm) + "  ym: " + i2s(ym) + "  mb: " + i2s(mb);
		Text(s.c_str());
		TreePop();
	}
	End();
}
