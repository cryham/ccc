#include "App.h"
#include "AppMain.h"
#include "FileSystem.h"

#include <SFML/Graphics.hpp>
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <iostream>
#include <memory>
using namespace std;  using namespace sf;  using namespace ImGui::SFML;



AppMain::AppMain()
{	}

bool AppMain::Run()
{
	FileSystem::Init();
	cout << FileSystem::GetInfo();
	
	
	//  laod Settings first
	//------------------
	unique_ptr<App> app = make_unique<App>();
	app->set.Load();
	Settings& set = app->set;


	//  Create window
	//------------------------------------------------
	//VideoMode vm = VideoMode::getDesktopMode();
	//--vm.height;  // fix

	app->pWindow = make_unique<RenderWindow>(
		VideoMode(set.xwSize, set.ywSize),
		"Crystal Color Center", // Title
		Style::Default, ContextSettings());

	app->pWindow->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(60);
	app->pWindow->setPosition(Vector2i(set.xwPos, set.ywPos));

	//  icon
	string data = FileSystem::Data()+"/";
	Image icon;
	if (icon.loadFromFile(data+"icon.png"))
		app->pWindow->setIcon(32, 32, icon.getPixelsPtr());


	//  ImGui
	//------------------
	Init(*app->pWindow.get());
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
	Vector2u ws = app->pWindow->getSize();
	app->Resize(ws.x, ws.y);
	app->Init();


	//  Load data
	//------------------------------------------------
	app->pFont = make_unique<Font>();
	if (!app->pFont->loadFromFile(data+"DejaVuLGCSans.ttf"))
	{	cout << "Can't load .ttf" << endl;  }

	Texture tex;
	if (!tex.loadFromFile(data+"white.png"))
	{	cout << "Can't load white.png" << endl;  }


	//  pass to app
	app->pBackgr = make_unique<Sprite>(tex);
	app->text.setFont(*app->pFont.get());
	app->text.setCharacterSize(app->set.iFontH);
	//app.Fy = font.getLineSpacing();


	//  Loop
	//------------------------------------------------
	Clock timer;
	while (app->pWindow->isOpen())
	{
		//  Process events
		//------------------
		Event e;
		while (app->pWindow->pollEvent(e))
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
			case Event::Closed:		set.GetWndDim(app->pWindow.get());  app->pWindow->close();  break;
			}
		}
		sf::Time time = timer.restart();
		Update(*app->pWindow, time);
		app->dt = time.asSeconds();

		//  Draw
		//------------------
		app->Gui();

		app->pWindow->resetGLStates();

		app->Graph();

		ImGui::Render();

		app->pWindow->display();

		//Sleep(0.20f);
	}

	//  dtor
	//------------------
	set.Save();

	ImGui::Shutdown();
	return true;
}
