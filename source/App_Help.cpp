#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
#include "Util.h"
using namespace std;  using namespace ImGui;


//  Help window
///-----------------------------------------------------------------------------
void App::Help()
{
	//  dim, clr
	const int sx = 1000, sy = 700, syc = sy-80;
	const static ImVec4 c0(0.93f,0.97f,1.f, 1.f),
		c1(0.85f,0.92f,1.f, 1.f), c2(0.6f,0.85f,1.f, 1.f), c3(0.5f,0.7f,0.9f, 1.f),
		cl2(0.6f,0.65f,0.7f, 0.7f);

	//  utils
	#define H(k,t)   TextColored(c1, k);  SameLine(110);  TextColored(c2, t);
	#define H3(k,t)  TextColored(c2, k);  SameLine(110);  TextColored(c3, t);


	//  center wnd
	SetNextWindowSize(ImVec2(sx, sy), ImGuiSetCond_Always);
	SetNextWindowPosCenter(ImGuiSetCond_Always);

	bool help = true, e;
	Begin("Help - Keyboard and mouse", &help, ImGuiWindowFlags_ShowBorders);

	//  ccc  ver
	SameLine(350);
	TextColored(c0, "Crystal Color Center");
	string sv = "version ";  sv += f2s(set.ver / 100.f);
	SameLine(550);  Text(sv.c_str());
	//SameLine(sx-80);  e = Button("Close");  if (e)  bHelp = 0;
	Sep(15);

//--  column 1
	float x = GetWindowContentRegionWidth(), xCol = x * 0.33f;
	BeginChild("Sub1", ImVec2(xCol, syc), true);

	TextColored(c0, "Main");
	Line(cl2);
	H("Esc", "Close");

	//  tab
	H("F1", "focus Edit controls");
	H("F2", "focus patterns List");

	Sep(10);
	H("Ctrl-F1", "Help window");
	H("F3", "Settings tab");

	//  load, save
	Sep(20);
	H("F4", "Save project");
	H("F5", "Reload project");

	Sep(10);
	H("F10", "New, clear");
	Sep(10);
	H("F9", "Import");
	H("F8", "Export");
	Sep(10);
	H("F7", "Start program");

//--  column 2
	EndChild();  SameLine();
	BeginChild("Sub2", ImVec2(xCol, syc), true);

	//  arrows, cursor move
	TextColored(c0, "Navigation");
	Line(cl2);
	H("Arrows or LMB", "");
	H("", "move cursor");

	//  page, line offset
	Sep(5);
	H("PageUp, Down or Wheel", "");
	H("", "scroll list");
	H3("", "shift  less,  ctrl, alt  more");

	Sep(10);
	H("Home, End", "first, last in row");
	H3("", "ctrl  in list");

	Sep(20);
	H("Ins", "Insert new");
	H3("", "shift  at top,  ctrl  at end");
	H("alt-Ins", "insert white, to split");
	H("alt-Del", "Delete current");
	Sep(10);
	H("alt-LMB", "Move current pattern");
	H("", "(or row) to cursor");
	Sep(5);
	H("RMB", "Select row");

//--  column 3
	EndChild();  SameLine();
	BeginChild("Sub3", ImVec2(xCol, syc), true);

	//  color
	TextColored(c0, "Other");
	Line(cl2);
	H("alt-C", "copy color");
	H("alt-S or V", "paste color");
	Sep(10);
	H("alt-D", "toggle Directory");
	H("alt-H", "toggle Hidden");
	H("alt-G", "toggle Group");
	Sep(10);
	H("alt-F", "focus Search");
	H("Enter", "go to next match");
	H("Backspace", "go to previous");

	Sep(10);
	H("F11, F12 or alt-Wheel", "");
	H("", "Font size");
	EndChild();

	#undef H
	End();
}
