#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
#include "Util.h"
using namespace ImGui;


//  Gui draw and process
///-----------------------------------------------------------------------------
void App::Gui()
{
	SetNextWindowPos( ImVec2(xs, 10),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(300/*xe-xs*/, 400), ImGuiSetCond_Always);
	const ImVec2 sep(100, 20);

	bool open = true;
	Begin("Controls", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	float i = 4.f;
	PushStyleColor(ImGuiCol_Button, ImColor::HSV(i/7.0f, 0.6f, 0.3f));
	PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(i/7.0f, 0.7f, 0.7f));
	PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(i/7.0f, 0.8f, 0.8f));

	Button("Save");  SameLine();  Button("Cancel");
	PopStyleColor(3);
	Dummy(sep);

	Pat* p = nullptr;
	if (lCur >= 0 && lCur < li.pat.size())
		p = &li.pat[lCur];

	/*static bool no_menu = false;
	if (TreeNode("Checkbox"))
	{
		static bool selected[3] = { false, false, false };
		Selectable("main.c", &selected[0]);  SameLine();  Text(" 2,345 bytes");
		Checkbox("No menu", &no_menu);
		Text("Hello!");
		TreePop();
	}/**/

	//static char buf[256]="";
	bool e = InputText("Pattern", pat, sizeof(pat)-1);
	if (e && p)
		p->s = pat;
	Dummy(sep);
//	Separator();
//	static ImVec4 col = ImVec4(0.5f,0.75f,1.f,1.0f);
//	static float sf = 36.0f;
//	DragFloat("Size", &sf, 0.2f, 2.0f, 72.0f, "%.0f");

//	const ImVec4 cl(r/255.f, g/255.f, b/255.f, 1.f);
//	ColorButton(cl, 70, false);
	ImDrawList* draw_list = GetWindowDrawList();
	float x,y, s=40, sz=s+10;
	const ImVec2 q = GetCursorScreenPos();  x = q.x;  y = q.y;
	ImColor c(r,g,b);
	draw_list->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x+s, y+s), c,c,c,c);
	Dummy(ImVec2(sz, sz));

	//Separator();
//	ColorEdit3("Color", &col.x);
//	static int r = 120;
	e = SliderInt("R", &r, 0, 255, "");  SameLine();  Text(i2s(r).c_str());  if (e && p)  p->c.r = r;
	e = SliderInt("G", &g, 0, 255, "");  SameLine();  Text(i2s(g).c_str());  if (e && p)  p->c.g = g;
	e = SliderInt("B", &b, 0, 255, "");  SameLine();  Text(i2s(b).c_str());  if (e && p)  p->c.b = b;

#if 0
	Dummy(sep);

	//  current info  -----
	y += yw + 20;
	Clr(180,120,120);  s = "R: " + i2s(cCur.r);  Txt(x, y);  y += yw;
	Clr(120,180,120);  s = "G: " + i2s(cCur.g);  Txt(x, y);  y += yw;
	Clr( 60,150,210);  s = "B: " + i2s(cCur.b);  Txt(x, y);  y += yw;

	//  status  -----
	Clr(185,225,255);
	s = "Patterns: " + i2s(li.pat.size()) +
		"  Colors: " + i2s(li.clr.size());
	Text(0, ye - iFontH);

	//  debug  -----
	//return;
	Clr(100,150,200);
	s = "xs: " + i2s(xs) + " xe: " + i2s(xe) + " ye: " + i2s(ye);
	Text(xe - 300, ye - 2*iFontH);
	s = "xm: " + i2s(xm) + " ym: " + i2s(ym) + " mb: " + i2s(mb);
	Text(xe - 300, ye - iFontH);
#endif
	End();
}
