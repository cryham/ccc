#include <SFML/Graphics.hpp>
#include "AppMain.h"
#include "App.h"
using namespace std;


AppMain::AppMain()
	:window(0)
{
}

bool AppMain::Run()
{

	//  Create window  (full screen, no border)
	//------------------------------------------------
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	--vm.height;  // fix

	window = new sf::RenderWindow(
		vm, "ccc", // Title
		sf::Style::None, sf::ContextSettings());

	window->setVerticalSyncEnabled(true);
	window->setPosition(sf::Vector2i(0,0));


	//  Init app
	App* app = new App();
	app->xe = vm.width;  app->ye = vm.height;
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

	app->pWindow = window;
	app->pBackgr = &back;
	app->pFont = &font;
	app->text.setFont(font);
	app->text.setCharacterSize(app->iFontH);
	//app.Fy = font.getLineSpacing();


	//  Loop
	//------------------------------------------------
	while (window->isOpen())
	{
		//  Process events
		//------------------
		sf::Event e;
		while (window->pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::MouseMoved:
				app->Mouse(e.mouseMove.x, e.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				app->mb = e.mouseButton.button + 1;
				break;
			case sf::Event::MouseButtonReleased:
				app->mb = 0;
				break;

			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Escape)  // Esc - Close
					window->close();
				else
				if (!app->KeyDown(e.key))
					window->close();
				break;

			case sf::Event::Closed:
				window->close();  break;
			}
		}

		//  Draw
		//------------------
		window->clear();

		app->Graph();

		window->display();

		//sf::Sleep(0.20f);
	}

	delete window;
	delete app;
	return true;
}
