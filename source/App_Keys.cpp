#include "App.h"

#define  ret  return true;


//  Keys input
///-----------------------------------------------------------------------------
bool App::KeyDown(const sf::Event::KeyEvent& key)
{
	using namespace sf;

	int lMax = li.pat.size();
	switch (key.code)
	{
		//  arrows, move
		case Keyboard::Left:  ret
		case Keyboard::Right: ret

		case Keyboard::Up:	  lOfs--;  if (lOfs < 0)  lOfs = 0;  ret
		case Keyboard::Down:  lOfs++;  if (lOfs >= lMax)  lOfs = lMax-1;  ret

		case Keyboard::PageUp:	  lOfs-=4;  if (lOfs < 0)  lOfs = 0;  ret
		case Keyboard::PageDown:  lOfs+=4;  if (lOfs >= lMax)  lOfs = lMax-1;  ret

		//  font size  - =
		case Keyboard::Dash:  iFontH--;  if (iFontH < 0)  iFontH = 0;
			text.setCharacterSize(iFontH);  ret
		case Keyboard::Equal: iFontH++;  if (iFontH >= lMax)  iFontH = lMax-1;
			text.setCharacterSize(iFontH);  ret
	}
	ret
}

void App::Mouse(int x, int y)
{
	xm = x;  ym = y;
}
