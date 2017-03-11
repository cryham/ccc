#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
//#include "Util.h"


//  Gui draw and process
///-----------------------------------------------------------------------------
void App::Gui()
{
//	ImGui::ShowTestWindow();

	ImGui::SetNextWindowPos(ImVec2(xs,100), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(350,360), ImGuiSetCond_FirstUseEver);

	static bool open = true;
	ImGui::Begin("Controls", &open);//, 0 ? 0 : ImGuiWindowFlags_NoTitleBar);
//	ImGui::Font()
//	ImGui::Begin("Hello");
	float i = 4.f;
	ImGui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(i/7.0f, 0.6f, 0.3f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(i/7.0f, 0.7f, 0.7f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(i/7.0f, 0.8f, 0.8f));
	ImGui::Button("Save");  ImGui::SameLine();  ImGui::Button("Cancel");
	ImGui::PopStyleColor(3);

	static bool no_menu = false;
	if (ImGui::TreeNode("Checkbox"))
	{
		static bool selected[3] = { false, false, false };
		ImGui::Selectable("main.c", &selected[0]);  ImGui::SameLine();  ImGui::Text(" 2,345 bytes");
		ImGui::Checkbox("No menu", &no_menu);
		ImGui::Text("Hello!");
		ImGui::TreePop();
	}

//	ImGui::Separator();
//	ImGui::PushFont(font);
	static char buf[256]="abcdef";
	ImGui::InputText("UTF-8 input", buf, sizeof(buf));
	ImGui::Separator();
	static float sf = 36.0f;
	static ImVec4 col = ImVec4(0.5f,0.75f,1.f,1.0f);
	ImGui::DragFloat("Size", &sf, 0.2f, 2.0f, 72.0f, "%.0f");
//	ImGui::Separator();
	ImGui::ColorEdit3("Color", &col.x);
	static float f1=0.123f, f2=0.0f;
	ImGui::SliderFloat("Slider", &f1, 0.0f, 1.0f, "ratio = %.3f");
//	ImGui::PopFont();

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	float x=10, y=10, sz=10, spacing=10;
	const ImVec2 p = ImGui::GetCursorScreenPos();  x = p.x;  y = p.y;
	draw_list->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x+sz*8, y+sz*4), ImColor(0,0,0), ImColor(255,150,0), ImColor(255,255,230), ImColor(0,255,255));
	ImGui::Dummy(ImVec2((sz+spacing)*8, (sz+spacing)*3));
	ImGui::End();
}
