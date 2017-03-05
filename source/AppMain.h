#pragma once

namespace sf {  class RenderWindow;  }


class AppMain
{
public:
	
	sf::RenderWindow* window;
	
	AppMain();
	bool Run();
};
