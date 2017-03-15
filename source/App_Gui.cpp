#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
#include "Util.h"
using namespace std;
using namespace ImGui;
using namespace SFML;



//  Gui draw and process
///-----------------------------------------------------------------------------
void App::Gui()
{
	const int yDbg = 200;  // par


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
	/*if (tab == Tab_List || bHelp)
	{	sf::Event e;
		e.type = sf::Event::MouseButtonPressed;
		e.mouseButton.button = sf::Mouse::Left;
		e.mouseButton.x = 0;  e.mouseButton.y = 0;
		ProcessEvent(e);
		e.type = sf::Event::MouseButtonReleased;
		ProcessEvent(e);
	}/**/

	switch (tab)
	{
	case Tab_List:  //  -------------------------
	case Tab_Edit:
	{
		//  Properties title  -----
		Text("Properties");  Sep(20);

		Pat* p = nullptr;  // current, for edit, set
		if (iCur >= 0 && iCur < li.pat.size())
			p = &li.pat[iCur];

		//  pattern edit  __
		if (edFocus)  // after F2
		{	edFocus = false;
			SetKeyboardFocusHere();
		}
		PushItemWidth(180);
		e = InputText("Pattern", ed.pat, sizeof(ed.pat));
		if (e && p)  p->s = ed.pat;  // set
		PopItemWidth();
		Sep(20);

		//  color rect  []
		ImDrawList* dl = GetWindowDrawList();
		const ImVec2 q = GetCursorScreenPos();
		float x = q.x, y = q.y, z=40, sz=z+10;
		ImColor c(ed.r, ed.g, ed.b);
		dl->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x+z, y+z), c,c,c,c);
		Dummy(ImVec2(sz, sz));  SameLine();  Text("Color  %02X%02X%02X",ed.r,ed.g,ed.b);  // hex clr

		//  r,g,b sliders  ==
		PushItemWidth(-120);  //PushAllowKeyboardFocus(false);
		e = SliderInt("R", &ed.r, 0, 255, "");  SameLine();  Text(i2s(ed.r).c_str());  if (e && p)  p->c.r = ed.r;  // set
		e = SliderInt("G", &ed.g, 0, 255, "");  SameLine();  Text(i2s(ed.g).c_str());  if (e && p)  p->c.g = ed.g;
		e = SliderInt("B", &ed.b, 0, 255, "");  SameLine();  Text(i2s(ed.b).c_str());  if (e && p)  p->c.b = ed.b;
		PopItemWidth();
		Dummy(sep);

		//  checks  ...
		//e = Checkbox("Dir",  &ed.dir);  if (e && p)  p->dir = ed.dir;  SameLine();  // set
		//e = Checkbox("Link", &ed.lnk);  if (e && p)  p->lnk = ed.lnk;  SameLine();
		//e = Checkbox("Exe",  &ed.exe);  if (e && p)  p->exe = ed.exe;  //SameLine();

		//  attrib  own, or from checks
		Sep(20);
		PushItemWidth(100);
		e = InputText("Attr", ed.attr, sizeof(ed.attr));
		if (e && p)  p->attr = ed.attr;  // set
		PopItemWidth();

		//  group todo sort
		/*Sep(20);
		PushItemWidth(80);
		e = DragInt("Group", &ed.grp, 0.1f);  ed.grp = std::min(10, std::max(-10, ed.grp));
		if (e && p)  p->grp = ed.grp;  // set
		//e = SliderInt("Group", &ed.grp, -120, 120, "");  SameLine();  Text(i2s(ed.grp).c_str());  if (e && p)  p->grp = ed.grp;  // set
		PopItemWidth();/**/


		//  quick tools  -----
		Sep(40);  Line(cl0);  Sep(10);
		Text("Search");  Sep(20);

		if (sFind[0]) {  SameLine();  Text("Found: %d / %d", iFound, iFoundAll);  }
		PushItemWidth(180);
		e = InputText("", sFind, sizeof(sFind));  SameLine();  if (e)  DoFind();
		PopItemWidth();
		e = Button("X");  if (e) {  sFind[0]=0;  DoFind();  }

		Sep(20);
		Text("Project");
		Sep(10);
		e = Button("Save F4");    if (e)  Save();  SameLine();
		e = Button("Reload F5");  if (e)  Load();
		///  status  -----
		Status& st = status;
		if (!st.txt.empty() && st.cnt < st.end)
		{	SameLine(0, 20);
			TextColored(ImColor::HSV(st.hue, 0.5f, 1.f-float(st.cnt)/st.end),
						st.txt.c_str());
			++st.cnt;
		}
		Sep(5);
		e = Button("Export to DC F8");  if (e)  SaveDC();
		e = Button("Import from DC F9");  if (e)  LoadDC();

	}	break;


	case Tab_Settings:  // -----
	{
		PushItemWidth(xSplit-80);
		Text("Dimensions");
		Sep(20);
		Text("Font Height");
		e = SliderInt("", &set.iFontH, 1, 32, "");  SameLine();  Text(i2s(set.iFontH).c_str());  if (e)  IncFont(0);
		Text("Line Y Spacing");
		e = SliderInt("", &set.iLineH,-2, 12, "");  SameLine();  Text(i2s(set.iLineH).c_str());
		Text("Item X Spacing");
		e = SliderFloat("", &set.fXMargin, 0.1f, 2.f, "");  SameLine();  Text(f2s(set.fXMargin).c_str());
		Text("Splitter");
		PushItemWidth(140);
		e = InputFloat("", &set.fSplit, 0.01f, 0.1f, 2);  if (e)  UpdSplit();  //-
		PopItemWidth();
		Sep(20);
		PopItemWidth();

		PushItemWidth(xSplit-40);
		Text("Paths");
		Sep(20);
		Text("Project file");
		e = InputText("", set.pathProj, sizeof(set.pathProj));
		Text("doublecmd.xml location");
		e = InputText("", set.pathDCxml, sizeof(set.pathDCxml));
		Text("Double Commander executable");
		e = InputText("", set.pathDCexe, sizeof(set.pathDCexe));
		PopItemWidth();

		Sep(20);
		Text("Settings");
		e = Button("Save");  if (e)  set.Save();  SameLine();
		e = Button("Reload");  if (e)  set.Load();
		Sep(20);
		e = Button("Defaults");  if (e)  set.Default();
	}	break;

	}
	End();


	if (bHelp)  Help();


	//  debug  wnd  =====
	SetNextWindowPos( ImVec2(0, yWindow-yDbg),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(xSplit, yDbg), ImGuiSetCond_Always);

	Begin("Status", &open, wfl);

	string s =  // -----
		"Patterns: " + i2s(li.pat.size()) +
		"  Colors: " + i2s(li.clr.size());
	Text(s.c_str());
	Sep(20);

	if (TreeNode("Debug"))
	{
		string s;
		s = "Cur: " + i2s(iCur) + "  Line: " + i2s(line);
		Text(s.c_str());
		s = "iCur: " + i2s(xSplit) + " xe: " + i2s(xWindow) + " | ye: " + i2s(yWindow);
		Text(s.c_str());
		s = "xs: " + i2s(xSplit) + " xe: " + i2s(xWindow) + " | ye: " + i2s(yWindow);
		Text(s.c_str());
		s = "xm: " + i2s(xm) + " ym: " + i2s(ym) + " mb: " + i2s(mb);
		Text(s.c_str());
		TreePop();
	}

	End();
}
