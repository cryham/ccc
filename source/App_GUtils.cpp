#include "../libs/imgui.h"
#include "App.h"
#include "Util.h"
using namespace ImGui;
using namespace std;


//  Gui look and colors
//------------------------------------------------------------------
void App::SetupGuiClr()
{
	ImGuiStyle& st = ImGui::GetStyle();
	st.WindowPadding = ImVec2(20,6);
	st.WindowMinSize = ImVec2(100,20);
	st.WindowRounding = 5;  st.ChildWindowRounding = 1;
	st.FramePadding = ImVec2(5,2);  st.FrameRounding = 0;
	st.ItemSpacing  = ImVec2(11,3);  //`
	st.ItemInnerSpacing = ImVec2(11,4);
	st.IndentSpacing = 14.f;
	st.ColumnsMinSpacing = 21.f;
	st.ScrollbarSize = 18.f;  st.ScrollbarRounding = 0.f;
	st.GrabMinSize = 20.f;  st.GrabRounding = 0.f;
	st.AntiAliasedLines = 1;  st.AntiAliasedShapes = 1;  //style.CurveTessellationTol;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text]                  = ImVec4(0.79f, 0.83f, 1.00f, 0.87f);
	style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.59f, 0.62f, 0.75f, 0.51f);
	style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.03f, 0.03f, 0.08f, 0.70f);
	style.Colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.65f);
	style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.05f, 0.05f, 0.10f, 0.82f);
	style.Colors[ImGuiCol_Border]                = ImVec4(0.13f, 0.13f, 0.20f, 0.81f);
	style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.80f, 0.83f, 1.00f, 0.11f);
	style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.67f, 0.71f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.70f, 0.80f, 1.00f, 0.48f);
	style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.27f, 0.27f, 0.54f, 0.61f);
	style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.40f, 0.40f, 0.80f, 0.45f);
	style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.32f, 0.32f, 0.63f, 0.29f);
	style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.45f, 0.45f, 0.55f, 0.19f);
	style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.14f, 0.13f, 0.22f, 0.60f);
	style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.42f, 0.42f, 0.85f, 0.30f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.50f, 0.50f, 1.00f, 0.40f);
	style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.50f, 1.00f, 0.46f);
	style.Colors[ImGuiCol_ComboBg]               = ImVec4(0.04f, 0.04f, 0.06f, 1.00f);
	style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.29f, 0.39f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.36f, 0.40f, 0.54f, 0.69f);
	style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.79f, 0.82f, 1.00f, 0.67f);
	style.Colors[ImGuiCol_Button]                = ImVec4(0.47f, 0.43f, 0.85f, 0.30f);
	style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.24f, 0.22f, 0.47f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.27f, 0.27f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Header]                = ImVec4(0.58f, 0.58f, 0.90f, 0.07f);
	style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.45f, 0.45f, 0.90f, 0.17f);
	style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.53f, 0.53f, 0.87f, 0.24f);
	style.Colors[ImGuiCol_Column]                = ImVec4(0.49f, 0.49f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.60f, 0.65f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive]          = ImVec4(0.70f, 0.79f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.75f, 0.89f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_CloseButton]           = ImVec4(0.41f, 0.41f, 0.66f, 0.50f);
	style.Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.54f, 0.50f, 0.85f, 0.60f);
	style.Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.70f, 0.72f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.76f, 0.81f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.61f, 0.69f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.55f, 0.76f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.13f, 0.20f, 0.76f, 0.47f);
	style.Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

}


//  draw utils
//------------------------------------------------------------------

//  write out text
int App::Txt(int x, int y, bool draw)
{
	//if (!window)  return;
	text.setString(str);
	text.setStyle(bold ? sf::Text::Bold : sf::Text::Regular);
	text.setColor(clr);
	text.setPosition(x, y);
	if (draw)  pWindow->draw(text);
	return text.getLocalBounds().width;  // advance x pos
}

//  clear rect
void App::Rect(int x, int y,  int sx, int sy, const SClr& c)
{
	Rect(x, y,  sx, sy, c.b, c.g, c.r);
}
void App::Rect(int x, int y,  int sx, int sy,
		  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
	//if (!pBackgr)  return;
	pBackgr->setScale(sx-x, sy-y);
	pBackgr->setPosition(x, y);
	pBackgr->setColor(sf::Color(b, g, r));
	pWindow->draw(*pBackgr);
}

//  frame rect, inefficient
void App::Frame(int x, int y,  int sx, int sy,  int d,
		  const SClr& c)
{
	Frame(x, y,  sx, sy,  d,  c.b, c.g, c.r);
}
void App::Frame(int x, int y,  int sx, int sy,  int d,
		  sf::Uint8 r, sf::Uint8 g, sf::Uint8 b)
{
	Rect(x,   y,    sx-d, y+d,  r, g, b);
	Rect(x,   sy-d, sx-d, sy,   r, g, b);
	Rect(x,   y,    x+d,  sy-d, r, g, b);
	Rect(sx-d,y,    sx,   sy,   r, g, b);
}
