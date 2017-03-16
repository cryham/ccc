#include "App.h"
using namespace sf;

#define  ret  return true;


//  Keys input
///-----------------------------------------------------------------------------
bool App::KeyDown(const sf::Event::KeyEvent& key)
{
	Mods(key);

	int lMax = li.pat.size()-1;  // lines
	int d = alt ? 20 : ctrl ? 12 : shift ? 1 : 4;  // diff
	int r = alt ? 10 : ctrl ? 4 : 1;


	//  help ctrl-F1 toggle, esc close
	if (key.code == Keyboard::F1 && ctrl ||
		key.code == Keyboard::Escape && bHelp)
	{	bHelp = 1-bHelp;  ret  }
	if (bHelp)  ret


	//  global keys
	switch (key.code)
	{
		//  esc close-
		case Keyboard::Escape:  set.GetWndDim(pWindow);  pWindow->close();  ret

		//  font size
		case Keyboard::F11:  IncFont(key.control ?-4:-1);  ret
		case Keyboard::F12:  IncFont(key.control ? 4: 1);  ret


		//  tab change --
		case Keyboard::F1:
			tab = Tab_Edit;  edFocus = true;  ret
		case Keyboard::F2:
			tab = ctrl||alt ? Tab_Settings : Tab_List;  ret

		case Keyboard::F3:
			tab = Tab_Settings;  ret

		//  load, save
		case Keyboard::F4:  Save();  ret
		case Keyboard::F5:  Load();  ret

		case Keyboard::F8:  SaveDC();  ret
		case Keyboard::F9:
			if (ctrl)	{	li.Default();  ret  }  // clear
			else		{	LoadDC();  ret  }

		case Keyboard::F7:  StartDC();  ret
	}

	//  list only  ----
	if (tab != Tab_List)
		ret

	switch (key.code)
	{
		//  arrows, cursor move
		case Keyboard::Left:  /*if (alt)  Move(shift,ctrl);  else*/  SetCur(iCur-r);  ret
		case Keyboard::Right: /*if (alt)  Move(shift,ctrl);  else*/  SetCur(iCur+r);  ret

		case Keyboard::Up:	  IncLine(-r);  ret
		case Keyboard::Down:  IncLine( r);  ret

		//  page, line offset
		case Keyboard::PageUp:	  line-=d;  if (line < 0)  line = 0;  ret
		case Keyboard::PageDown:  line+=d;  if (line > lMax)  line = lMax;  ret

		case Keyboard::Home:   First(ctrl);  ret
		case Keyboard::End:    Last(ctrl);  ret

		case Keyboard::Insert:  AddPat(shift, ctrl);  ret
	}

	if (alt)
	switch (key.code)
	{
		//  color
		case Keyboard::C:  CopyClr();  ret
		case Keyboard::S:
		case Keyboard::V:  PasteClr();  ret

		//  find
		case Keyboard::F:
			tab = Tab_Edit;  findFocus = true;  ret

		//  toggle checks
		//case Keyboard::D:  InvDir();  ret

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
	if (bHelp)  return;
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


//  utils input  ----
void App::Mouse(int x, int y)
{
	xm = x;  ym = y;
	if (tab == Tab_Edit && xm > xSplit)
		tab = Tab_List;
	else
	if (tab == Tab_List && xm < xSplit)
		tab = Tab_Edit;
}

void App::Mods(const sf::Event::KeyEvent& key)
{
	alt = key.alt;  ctrl = key.control;  shift = key.shift;  // mods
}

bool App::KeyUp(const sf::Event::KeyEvent& key)
{
	Mods(key);
}
