#include "App.h"

#define  ret  return true;


//  Keys input
///-----------------------------------------------------------------------------
bool App::KeyDown(const sf::Event::KeyEvent& key)
{
	using namespace sf;

	int lMax = li.pat.size()-1;  // lines

	if (key.alt)
	switch (key.code)
	{
		//  ctrl, move
		case Keyboard::Up:	  lCur-=16;  if (lCur < 0)  lCur = 0;  ret
		case Keyboard::Down:  lCur+=16;  if (lCur > lMax)  lCur = lMax;  ret

		case Keyboard::PageUp:	  lOfs-=16;  if (lOfs < 0)  lOfs = 0;  ret
		case Keyboard::PageDown:  lOfs+=16;  if (lOfs > lMax)  lOfs = lMax;  ret
	}
	else
	if (key.control)
	switch (key.code)
	{
		//  ctrl, move
		case Keyboard::Up:	  lCur-=4;  if (lCur < 0)  lCur = 0;  ret
		case Keyboard::Down:  lCur+=4;  if (lCur > lMax)  lCur = lMax;  ret

		case Keyboard::PageUp:	  lOfs-=8;  if (lOfs < 0)  lOfs = 0;  ret
		case Keyboard::PageDown:  lOfs+=8;  if (lOfs > lMax)  lOfs = lMax;  ret
	}
	else switch (key.code)
	{
		//  arrows, move
		case Keyboard::Left:  ret
		case Keyboard::Right: ret

		case Keyboard::Up:	  lCur--;  if (lCur < 0)  lCur = 0;  ret
		case Keyboard::Down:  lCur++;  if (lCur > lMax)  lCur = lMax-1;  ret

		//  page offset
		case Keyboard::PageUp:	  lOfs--;  if (lOfs < 0)  lOfs = 0;  ret
		case Keyboard::PageDown:  lOfs++;  if (lOfs > lMax)  lOfs = lMax;  ret


		//  font size  - =
		case Keyboard::Dash:  IncFont(-1);  ret
		case Keyboard::Equal: IncFont( 1);  ret


		//  load, save
		case Keyboard::F1:  li.LoadDC("doublecmd.xml");  ret
		case Keyboard::F2:  li.SaveDC("dc.xml");  ret
		case Keyboard::F8:  li.Default();  ret  // clear

		case Keyboard::F4:  li.Save("ccc.xml");  ret
		case Keyboard::F5:  li.Load("ccc.xml");  ret
	}
	ret
}

void App::IncFont(int d)
{
	iFontH += d;
	if (iFontH < 0)   iFontH = 0;
	if (iFontH > 32)  iFontH = 32;
	text.setCharacterSize(iFontH);
}

void App::Mouse(int x, int y)
{
	xm = x;  ym = y;
}
