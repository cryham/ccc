#include <SFML/Graphics.hpp>
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "AppMain.h"
#include "App.h"
using namespace std;


AppMain::AppMain()
	:window(0)
{	}

bool AppMain::Run()
{

	//  Create window
	//------------------------------------------------
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	--vm.height;  // fix

	window = new sf::RenderWindow(
		1 ? sf::VideoMode(1650,1050) : vm,
		"ccc", // Title
		1 ? sf::Style::Default : sf::Style::None,
		sf::ContextSettings());

	window->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(60);
	window->setPosition(sf::Vector2i(0,0));


	//  ImGui
	//------------------
	ImGui::SFML::Init(*window);
	//  font
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->ClearFonts();
	ImFont* fnt = io.Fonts->AddFontFromFileTTF("data/DejaVuLGCSans.ttf", 18);
	sf::Texture* fntTex = new sf::Texture;
	ImGui::SFML::createFontTexture(*fntTex);
	ImGui::SFML::setFontTexture(*fntTex);


	//  Init app
	//------------------
	App* app = new App();
	sf::Vector2u ws = window->getSize();
	app->Resize(ws.x, ws.y);
	app->Init();


	//  Load data
	//------------------------------------------------
	sf::Font font;
	if (!font.loadFromFile("data/DejaVuLGCSans.ttf"))
		{}  //Warning("Can't load .ttf","App Run");

	sf::Texture tex;
	if (!tex.loadFromFile("data/white.png"))
		{}  //Warning("Can't load white.png","App Run");

	sf::Sprite back(tex);

	//  pass to app
	app->pWindow = window;
	app->pBackgr = &back;
	app->pFont = &font;
	app->text.setFont(font);
	app->text.setCharacterSize(app->iFontH);
	//app.Fy = font.getLineSpacing();


	//  Loop
	//------------------------------------------------
	sf::Clock dt;
	while (window->isOpen())
	{
		//  Process events
		//------------------
		sf::Event e;
		while (window->pollEvent(e))
		{
			ImGui::SFML::ProcessEvent(e);

			switch (e.type)
			{
			case sf::Event::MouseMoved:				app->Mouse(e.mouseMove.x, e.mouseMove.y);  break;
			case sf::Event::MouseButtonPressed:		app->mb = e.mouseButton.button + 1;  break;
			case sf::Event::MouseButtonReleased:	app->mb = 0;  break;

			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Escape)  // Esc - Close
					window->close();
				else
				if (!app->KeyDown(e.key))
					window->close();
				break;

			case sf::Event::Resized:	app->Resize(e.size.width, e.size.height);  break;
			case sf::Event::Closed:		window->close();  break;
			}
		}
		ImGui::SFML::Update(*window, dt.restart());


		//  Draw
		//------------------
		app->Gui();

		//window->resetGLStates();
		window->clear();

		app->Graph();

		ImGui::Render();

		window->display();

		//sf::Sleep(0.20f);
	}

	//  dtor
	//------------------
	ImGui::Shutdown();
	delete window;
	delete app;
	return true;
}
