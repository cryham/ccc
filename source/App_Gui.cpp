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
	SetNextWindowPos( ImVec2(xs, 10),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(400/*xe-xs*/, ye-100), ImGuiSetCond_Always);
	const ImVec2 sep(100, 20), sep2(100, 40);

	bool open = true, e;
	Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	float i = 4.f;
	e = Button("Save F4");    if (e)  Save();  SameLine();
	e = Button("Reload F5");  if (e)  Load();

	//  status  -----
	if (!txtStatus.empty() && iStatus < maxStatus)
	{	SameLine(0, 20);
		TextColored(ImColor::HSV(hueStatus, 0.5f, 1.f-float(iStatus)/maxStatus),
					txtStatus.c_str());
		++iStatus;
	}
	Dummy(sep);

	//Selectable("main.c", &selected);
	//DragFloat("Size", &sf, 0.2f, 2.0f, 72.0f, "%.0f");


	//  Properties  -----
	Pat* p = nullptr;  // current, for edit, set
	if (iCur >= 0 && iCur < li.pat.size())
		p = &li.pat[iCur];

	//  pattern edit  __
	e = InputText("Pattern", ed.pat, sizeof(ed.pat)-1);
	if (e && p)  p->s = ed.pat;  // set
	Dummy(sep);

	//  color rect  []
	ImDrawList* dl = GetWindowDrawList();
	const ImVec2 q = GetCursorScreenPos();
	float x = q.x, y = q.y, z=40, sz=z+10;
	ImColor c(ed.r, ed.g, ed.b);
	dl->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x+z, y+z), c,c,c,c);
	Dummy(ImVec2(sz, sz));

	//  r,g,b sliders  ==
	e = SliderInt("R", &ed.r, 0, 255, "");  SameLine();  Text(i2s(ed.r).c_str());  if (e && p)  p->c.r = ed.r;  // set
	e = SliderInt("G", &ed.g, 0, 255, "");  SameLine();  Text(i2s(ed.g).c_str());  if (e && p)  p->c.g = ed.g;
	e = SliderInt("B", &ed.b, 0, 255, "");  SameLine();  Text(i2s(ed.b).c_str());  if (e && p)  p->c.b = ed.b;
	Dummy(sep);

	//  checks  ...
	e = Checkbox("Dir",  &ed.dir);  if (e && p)  p->dir = ed.dir;  SameLine();  // set
	e = Checkbox("Link", &ed.lnk);  if (e && p)  p->lnk = ed.lnk;  SameLine();
	e = Checkbox("Exe",  &ed.exe);  if (e && p)  p->exe = ed.exe;


	Dummy(sep2);  /// below -----
	//if (TreeNode("Status"))
	//  status  -----
	string s =
		"Patterns: " + i2s(li.pat.size()) +
		"  Colors: " + i2s(li.clr.size()) +
		"  Cur: " + i2s(iCur) +
		"  Line: " + i2s(line);
	Text(s.c_str());

	Dummy(sep);  // -----
	if (TreeNode("Settings"))
	{
		e = SliderInt("FontH", &iFontH, 1, 32, "");  SameLine();  Text(i2s(iFontH).c_str());  if (e)  IncFont(0);
		e = SliderInt("LineH", &iLineH, -2, 12, "");  SameLine();  Text(i2s(iLineH).c_str());
		e = InputText("Project file", proj, sizeof(proj)-1);
		TreePop();
	}

	Dummy(sep);  // -----
	if (TreeNode("Debug"))
	{
		s = "xs: " + i2s(xs) + " xe: " + i2s(xe) + " | ye: " + i2s(ye);
		Text(s.c_str());
		s = "xm: " + i2s(xm) + " ym: " + i2s(ym) + " mb: " + i2s(mb);
		Text(s.c_str());
		TreePop();
	}
	End();
}
