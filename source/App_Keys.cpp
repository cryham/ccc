#include "App.h"
#define  ret  return true;

//  Keys input
///-----------------------------------------------------------------------------
bool App::KeyDown(const sf::Event::KeyEvent& key)
{
	Mods(key);

	int lMax = li.pat.size()-1;  // lines
	int d = alt ? 20 : ctrl ? 12 : shift ? 1 : 4;  // diff
	int r = alt ? 10 : ctrl ? 4 : 1;

	using namespace sf;

	//  global keys
	switch (key.code)
	{
		//  esc close-
		case Keyboard::Escape:  pWindow->close();  ret

		//  font size
		case Keyboard::F11:  IncFont(key.control ?-4:-1);  ret
		case Keyboard::F12:  IncFont(key.control ? 4: 1);  ret


		//  tab change --
		case Keyboard::F1:  tab = ctrl||alt ? Tab_Help : Tab_Edit;  edFocus = true;  ret
		case Keyboard::F2:  tab = ctrl||alt ? Tab_Settings : Tab_List;  ret

		//  load, save
		case Keyboard::F8:
			if (ctrl)	{	li.Default();  ret  }  // clear
			else		{	li.SaveDC("dc.xml");  ret  }
		case Keyboard::F9:  li.LoadDC("doublecmd.xml");  ret

		case Keyboard::F4:  Save();  ret
		case Keyboard::F5:  Load();  ret

	}

	if (tab != Tab_List)
		ret

	switch (key.code)
	{
		//  esc close-
		case Keyboard::Escape:  pWindow->close();  ret

		//  arrows, cursor move
		case Keyboard::Left:  SetCur(iCur-r);  ret
		case Keyboard::Right: SetCur(iCur+r);  ret

		case Keyboard::Up:	  IncLine(-r);  ret
		case Keyboard::Down:  IncLine( r);  ret


		//  page, line offset
		case Keyboard::PageUp:	  line-=d;  if (line < 0)  line = 0;  ret
		case Keyboard::PageDown:  line+=d;  if (line > lMax)  line = lMax;  ret

		case Keyboard::Insert:  AddPat(shift, ctrl);  ret
	}

	if (alt)
	switch (key.code)
	{
		//  color
		case Keyboard::C:  CopyClr();  ret
		case Keyboard::S:
		case Keyboard::V:  SetClr();  ret

		//  toggle checks
		case Keyboard::D:  InvDir();  ret

		//  add, del
		//case Keyboard::A:		AddPat(shift, ctrl);  ret
		case Keyboard::Delete:  DelPat();  ret

		#if 0
		case Keyboard::Num1:  IncGrp(-1);  ret
		case Keyboard::Num2:  IncGrp( 1);  ret
		#endif
	}
	ret
}

void App::IncFont(int d)
{
	set.iFontH += d;
	if (set.iFontH < 1)   set.iFontH = 1;
	if (set.iFontH > 32)  set.iFontH = 32;
	text.setCharacterSize(set.iFontH);
}

void App::Wheel(float d)
{
	if (alt)
	{	d *= ctrl ? 4 : shift ? 1 : 2;
		IncFont(d);
		return;
	}
	d *= ctrl ? 12 : shift ? 1 : 4;
	int lMax = li.pat.size()-1;  // lines
	line -= d;
	if (line < 0)  line = 0;
	if (line > lMax)  line = lMax;
}

//  utils  ----
void App::Mouse(int x, int y)
{
	xm = x;  ym = y;
}

void App::Mods(const sf::Event::KeyEvent& key)
{
	alt = key.alt;  ctrl = key.control;  shift = key.shift;  // mods
}

bool App::KeyUp(const sf::Event::KeyEvent& key)
{
	Mods(key);
}
