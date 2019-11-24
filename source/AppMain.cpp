#include "App.h"
#include "AppMain.h"
#include "FileSystem.h"

#include <SFML/Graphics.hpp>
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <iostream>
#include <memory>
using namespace std;  using namespace sf;  using namespace ImGui::SFML;



bool AppMain::Run()
{
	FileSystem::Init();
	cout << FileSystem::GetInfo();
	
	
	//  laod Settings first
	//------------------
	set.Load();


	//  Create window
	//------------------------------------------------
	//VideoMode vm = VideoMode::getDesktopMode();
	//--vm.height;  // fix

	pWindow = make_unique<RenderWindow>(
		VideoMode(set.xwSize, set.ywSize),
		"Crystal Color Center", // Title
		Style::Default, ContextSettings());

	pWindow->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(60);
	pWindow->setPosition(Vector2i(set.xwPos, set.ywPos));

	//  icon
	string data = FileSystem::Data()+"/";
	Image icon;
	if (icon.loadFromFile(data+"icon.png"))
		pWindow->setIcon(32, 32, icon.getPixelsPtr());


	//  ImGui
	//------------------
	Init(*pWindow.get());
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;  io.LogFilename = nullptr;  // nope
	io.Fonts->ClearFonts();
	//  font
	string sfont = data+"DejaVuLGCSans.ttf";
	ImFont* fnt = io.Fonts->AddFontFromFileTTF(
					  sfont.c_str(), set.iFontGui);
	Texture* fntTex = new Texture;
	createFontTexture(*fntTex);
	setFontTexture(*fntTex);


	//  Init app
	//------------------
	Vector2u ws = pWindow->getSize();
	Resize(ws.x, ws.y);
	InitApp();


	//  Load data
	//------------------------------------------------
	pFont = make_unique<Font>();
	if (!pFont->loadFromFile(data+"DejaVuLGCSans.ttf"))
	{	cout << "Can't load .ttf" << endl;  }

	Texture tex;
	if (!tex.loadFromFile(data+"white.png"))
	{	cout << "Can't load white.png" << endl;  }


	//  pass to app
	pBackgr = make_unique<Sprite>(tex);
	text.setFont(*pFont.get());
	text.setCharacterSize(set.iFontH);
	//app.Fy = font.getLineSpacing();


	//  Loop
	//------------------------------------------------
	Clock timer;
	while (pWindow->isOpen())
	{
		//  Process events
		//------------------
		Event e;
		while (pWindow->pollEvent(e))
		{
			ProcessEvent(e);

			switch (e.type)
			{
			case Event::MouseMoved:				Mouse(e.mouseMove.x, e.mouseMove.y);  break;
			case Event::MouseWheelScrolled:		Wheel(e.mouseWheelScroll.delta);  break;

			case Event::MouseButtonPressed:		mb = e.mouseButton.button + 1;  break;
			case Event::MouseButtonReleased:	mb = 0;  break;

			case Event::KeyPressed:		KeyDown(e.key);  break;
			case Event::KeyReleased:	KeyUp(e.key);  break;

			case Event::Resized:	Resize(e.size.width, e.size.height);  break;
			case Event::Closed:		set.GetWndDim(pWindow.get());  pWindow->close();  break;
			}
		}
		sf::Time time = timer.restart();
		Update(*pWindow, time);
		dt = time.asSeconds();

		//  Draw
		//------------------
		Gui();

		pWindow->resetGLStates();

		Graph();

		ImGui::Render();

		pWindow->display();

		//Sleep(0.20f);
	}

	//  dtor
	//------------------
	set.Save();

	ImGui::Shutdown();
	return true;
}
