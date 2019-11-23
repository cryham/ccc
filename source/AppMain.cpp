#include "App.h"
#include "AppMain.h"
#include "FileSystem.h"

#include <SFML/Graphics.hpp>
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <iostream>
using namespace std;  using namespace sf;  using namespace ImGui::SFML;



AppMain::AppMain()
{	}

bool AppMain::Run()
{
	FileSystem::Init();
	cout << FileSystem::GetInfo();
	
	
	//  laod Settings first
	//------------------
	App* app = new App();
	app->set.Load();
	Settings& set = app->set;


	//  Create window
	//------------------------------------------------
	//VideoMode vm = VideoMode::getDesktopMode();
	//--vm.height;  // fix

	sf::RenderWindow* window = new RenderWindow(
		VideoMode(set.xwSize, set.ywSize),
		"Crystal Color Center", // Title
		Style::Default, ContextSettings());

	window->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(60);
	window->setPosition(Vector2i(set.xwPos, set.ywPos));

	//  icon
	string data = FileSystem::Data()+"/";
	Image icon;
	if (icon.loadFromFile(data+"icon.png"))
		window->setIcon(32, 32, icon.getPixelsPtr());


	//  ImGui
	//------------------
	Init(*window);
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;  io.LogFilename = nullptr;  // nope
	io.Fonts->ClearFonts();
	//  font
	string sfont = data+"DejaVuLGCSans.ttf";
	ImFont* fnt = io.Fonts->AddFontFromFileTTF(
					  sfont.c_str(), app->set.iFontGui);
	Texture* fntTex = new Texture;
	createFontTexture(*fntTex);
	setFontTexture(*fntTex);


	//  Init app
	//------------------
	Vector2u ws = window->getSize();
	app->Resize(ws.x, ws.y);
	app->Init();


	//  Load data
	//------------------------------------------------
	Font font;
	if (!font.loadFromFile(data+"DejaVuLGCSans.ttf"))
		{}  //Warning("Can't load .ttf","App Run");

	Texture tex;
	if (!tex.loadFromFile(data+"white.png"))
		{}  //Warning("Can't load white.png","App Run");

	Sprite back(tex);

	//  pass to app
	app->pWindow = window;
	app->pBackgr = &back;
	app->pFont = &font;
	app->text.setFont(font);
	app->text.setCharacterSize(app->set.iFontH);
	//app.Fy = font.getLineSpacing();


	//  Loop
	//------------------------------------------------
	Clock timer;
	while (window->isOpen())
	{
		//  Process events
		//------------------
		Event e;
		while (window->pollEvent(e))
		{
			ProcessEvent(e);

			switch (e.type)
			{
			case Event::MouseMoved:				app->Mouse(e.mouseMove.x, e.mouseMove.y);  break;
			case Event::MouseWheelScrolled:		app->Wheel(e.mouseWheelScroll.delta);  break;

			case Event::MouseButtonPressed:		app->mb = e.mouseButton.button + 1;  break;
			case Event::MouseButtonReleased:	app->mb = 0;  break;

			case Event::KeyPressed:		app->KeyDown(e.key);  break;
			case Event::KeyReleased:	app->KeyUp(e.key);  break;

			case Event::Resized:	app->Resize(e.size.width, e.size.height);  break;
			case Event::Closed:		set.GetWndDim(window);  window->close();  break;
			}
		}
		sf::Time time = timer.restart();
		Update(*window, time);
		app->dt = time.asSeconds();

		//  Draw
		//------------------
		app->Gui();

		window->resetGLStates();

		app->Graph();

		ImGui::Render();

		window->display();

		//Sleep(0.20f);
	}

	//  dtor
	//------------------
	set.Save();

	ImGui::Shutdown();
	delete window;
	delete app;
	return true;
}
