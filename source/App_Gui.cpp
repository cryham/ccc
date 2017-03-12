#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
#include "Util.h"
using namespace ImGui;
using namespace std;


//  Gui draw and process
///-----------------------------------------------------------------------------
void App::Gui()
{
	const int yDbg = 200;
#if 0  // right
	SetNextWindowPos( ImVec2(xSplit, 10),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(xWindow-xSplit, yWindow-20), ImGuiSetCond_Always);
#else  // left
	SetNextWindowPos( ImVec2(0, 10),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(xSplit, yWindow-200-10), ImGuiSetCond_Always);
#endif
	const ImVec2 sep(100, 20), sep2(100, 40);

	bool e, open = true;
	Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	//  tabs
	TabLabels(Tab_ALL, tabNames, tab, true);
	Dummy(sep);

	//  unfocus gui, keys for list
	if (tab == Tab_List)
	{	sf::Event e;
		e.type = sf::Event::MouseButtonPressed;
		e.mouseButton.button = sf::Mouse::Left;
		e.mouseButton.x = 0;  e.mouseButton.y = 0;
		ImGui::SFML::ProcessEvent(e);
		e.type = sf::Event::MouseButtonReleased;
		ImGui::SFML::ProcessEvent(e);
	}

switch (tab)
{
case Tab_List:  //  -------------------------
case Tab_Edit:
{
	//  quick
	e = Button("Save F4");    if (e)  Save();  SameLine();
	e = Button("Reload F5");  if (e)  Load();

	///  status  -----
	if (!txtStatus.empty() && iStatus < maxStatus)
	{	SameLine(0, 20);
		TextColored(ImColor::HSV(hueStatus, 0.5f, 1.f-float(iStatus)/maxStatus),
					txtStatus.c_str());
		++iStatus;
	}
	Dummy(sep);


	//  Properties
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
	Dummy(sep);

	//  color rect  []
	ImDrawList* dl = GetWindowDrawList();
	const ImVec2 q = GetCursorScreenPos();
	float x = q.x, y = q.y, z=40, sz=z+10;
	ImColor c(ed.r, ed.g, ed.b);
	dl->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x+z, y+z), c,c,c,c);
	Dummy(ImVec2(sz, sz));

	//  r,g,b sliders  ==
	PushItemWidth(260);  //PushAllowKeyboardFocus(false);
	e = SliderInt("R", &ed.r, 0, 255, "");  SameLine();  Text(i2s(ed.r).c_str());  if (e && p)  p->c.r = ed.r;  // set
	e = SliderInt("G", &ed.g, 0, 255, "");  SameLine();  Text(i2s(ed.g).c_str());  if (e && p)  p->c.g = ed.g;
	e = SliderInt("B", &ed.b, 0, 255, "");  SameLine();  Text(i2s(ed.b).c_str());  if (e && p)  p->c.b = ed.b;
	PopItemWidth();
	Dummy(sep);

	//  checks  ...
	e = Checkbox("Dir",  &ed.dir);  if (e && p)  p->dir = ed.dir;  SameLine();  // set
	e = Checkbox("Link", &ed.lnk);  if (e && p)  p->lnk = ed.lnk;  SameLine();
	e = Checkbox("Exe",  &ed.exe);  if (e && p)  p->exe = ed.exe;  //SameLine();

	//  attrib  own, or from checks
	Dummy(sep);
	PushItemWidth(100);
	e = InputText("Attr", ed.attr, sizeof(ed.attr));
	if (e && p)  p->attr = ed.attr;  // set
	PopItemWidth();

	//  group todo sort
	Dummy(sep);
//	PushItemWidth(80);
	e = DragInt("Group", &ed.grp, 0.1f);  ed.grp = std::min(10, std::max(-10, ed.grp));
	if (e && p)  p->grp = ed.grp;  // set
//	e = SliderInt("Group", &ed.grp, -120, 120, "");  SameLine();  Text(i2s(ed.grp).c_str());  if (e && p)  p->grp = ed.grp;  // set
//	PopItemWidth();

}	break;


case Tab_Settings:  // -----
{
	PushItemWidth(xSplit-10);
	Text("Dimensions");
	Dummy(sep);
	Text("Font Height");
	e = SliderInt("", &set.iFontH, 1, 32, "");  SameLine();  Text(i2s(set.iFontH).c_str());  if (e)  IncFont(0);
	Text("Line Y Spacing");
	e = SliderInt("", &set.iLineH,-2, 12, "");  SameLine();  Text(i2s(set.iLineH).c_str());
	Text("Item X Spacing");
	e = SliderFloat("", &set.fXMargin, 0.1f, 2.f, "");  SameLine();  Text(f2s(set.fXMargin).c_str());
	Text("Splitter");
	e = DragFloat("", &set.fSplit, 1.f, 0.1f, 0.9f, "%4.2f");  if (e)  UpdSplit();  //-
	Dummy(sep);

	Text("Paths");
	Dummy(sep);
	Text("Project file");
	e = InputText("", set.pathProj, sizeof(set.pathProj));
	Text("DC doublecmd.xml location");
	e = InputText("", set.pathDCxml, sizeof(set.pathDCxml));
	Text("DC exe location");
	e = InputText("", set.pathDCexe, sizeof(set.pathDCexe));
	PopItemWidth();
}	break;


case Tab_Help:  // -----
{
	Text("Crystal Color Center");
	Dummy(sep);

	Text("Ctrl-F1  Help");
	Dummy(sep);
	Text("F1  focus List");
	Text("F2  focus Edit");

	Dummy(sep);
	Text("Ctr-F2  Settings");
}	break;
}
	End();


	//  debug  -----
	SetNextWindowPos( ImVec2(0, yWindow-yDbg),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(xSplit, yDbg), ImGuiSetCond_Always);

	Begin("Status", &open, 0/*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize/**/);

	string s =  // -----
		"Patterns: " + i2s(li.pat.size()) +
		"  Colors: " + i2s(li.clr.size());
	Text(s.c_str());

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
