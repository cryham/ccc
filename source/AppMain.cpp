#include <SFML/Graphics.hpp>
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "AppMain.h"
#include "App.h"
using namespace std;  using namespace sf;  using namespace ImGui::SFML;



AppMain::AppMain()
	:window(0)
{	}

bool AppMain::Run()
{
	//  laod Settings first
	//------------------
	App* app = new App();
	app->set.Load();
	Settings& s = app->set;


	//  Create window
	//------------------------------------------------
	//VideoMode vm = VideoMode::getDesktopMode();
	//--vm.height;  // fix

	window = new RenderWindow(
		VideoMode(s.xwSize, s.ywSize),
		"Crystal Color Center", // Title
		Style::Default, ContextSettings());

	window->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(60);
	window->setPosition(Vector2i(s.xwPos, s.ywPos));


	//  ImGui
	//------------------
	Init(*window);
	//  font
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = 0;  io.LogFilename = 0;  // nope
	io.Fonts->ClearFonts();
	ImFont* fnt = io.Fonts->AddFontFromFileTTF("data/DejaVuLGCSans.ttf", app->set.iFontGui);
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
	if (!font.loadFromFile("data/DejaVuLGCSans.ttf"))
		{}  //Warning("Can't load .ttf","App Run");

	Texture tex;
	if (!tex.loadFromFile("data/white.png"))
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
			case Event::Closed:		s.GetWndDim(window);  window->close();  break;
			}
		}
		sf::Time time = timer.restart();
		Update(*window, time);
		app->dt = time.asSeconds();

		//  Draw
		//------------------
		app->Gui();

		window->resetGLStates();
		window->clear();

		app->Graph();

		ImGui::Render();

		window->display();

		//Sleep(0.20f);
	}

	//  dtor
	//------------------
	s.Save();

	ImGui::Shutdown();
	delete window;
	delete app;
	return true;
}
