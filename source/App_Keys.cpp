#include "App.h"
using namespace sf;

#define  ret  return true;


//  Keys input
///-----------------------------------------------------------------------------
bool App::KeyDown(const sf::Event::KeyEvent& key)
{
	Mods(key);

	int lMax = li.pat.size()-1;  // lines
	int dCur  = alt ? 1 : ctrl ? 4 : 1;


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
		case Keyboard::F11:  IncFont(ctrl ?-4:-1);  ret
		case Keyboard::F12:  IncFont(ctrl ? 4: 1);  ret


		//  tab change --
		case Keyboard::F1:  tab = Tab_Edit;  edFocus = true;  ret
		case Keyboard::F2:  tab = ctrl||alt ? Tab_Settings : Tab_List;  ret

		case Keyboard::F3:  tab = Tab_Settings;  ret

		//  load, save
		case Keyboard::F4:  Save();  ret
		case Keyboard::F5:  Load();  ret

		case Keyboard::F8:  Export();  ret
		case Keyboard::F9:  Import();  ret

		case Keyboard::F10: li.Default();  ret  // clear
		case Keyboard::F7:  StartExe();  ret
	}

	//  list only  ----
	if (tab != Tab_List)
		ret

	switch (key.code)
	{
		//  arrows, cursor move
		case Keyboard::Left:  SetCur(iCur-dCur);  ret
		case Keyboard::Right: SetCur(iCur+dCur);  ret

		case Keyboard::Up:	  IncLine(-dCur);  ret
		case Keyboard::Down:  IncLine( dCur);  ret

		//  page, line offset
		case Keyboard::PageUp:	 line -= dLine;  if (line < 0)    line = 0;    ret
		case Keyboard::PageDown: line += dLine;  if (line > lMax) line = lMax; ret

		case Keyboard::Home:  First(ctrl);  ret
		case Keyboard::End:   Last(ctrl);  ret

		//  add
		case Keyboard::Insert:  AddPat(shift, ctrl, alt);  ret

		//  next/prev find
		case Keyboard::BackSpace:  NextFind(-dFind);  ret
		case Keyboard::BackSlash:
		case Keyboard::Return:  NextFind(shift ? -dFind : dFind);  ret
	}

	if (alt)  // _alt_
	switch (key.code)
	{
		//  color copy
		case Keyboard::C:  CopyClr();  ret
		case Keyboard::S:
		case Keyboard::V:  PasteClr();  ret

		//  find
		case Keyboard::F:  tab = Tab_Edit;  findFocus = true;  ret

		//  toggle
		case Keyboard::D:  InvDir();  ret
		case Keyboard::H:  InvHide();  ret
		case Keyboard::G:  InvGroup();  ret

		//  del
		case Keyboard::Delete:  DelPat();  ret
	}
	ret
}
#undef ret


//  utils, mouse  ----
void App::Wheel(float d)
{
	if (xm < xSplit || bHelp)  return;

	if (alt)
	{	d *= ctrl ? 4 : shift ? 1 : 2;
		IncFont(d);
		return;
	}

	d *= dLine;
	int lMax = li.pat.size()-1;  // lines
	line -= d;
	if (line < 0)  line = 0;
	if (line > lMax)  line = lMax;
}

void App::Mouse(int x, int y)
{
	xm = x;  ym = y;
	if (dragSplit)
		return;
	if (tab == Tab_Edit && xm > xSplit)
		tab = Tab_List;
	else
	if (tab == Tab_List && xm < xSplit)
		tab = Tab_Edit;
}

//  utils, keys  ----
void App::IncFont(int d)
{
	set.iFontH += d;
	if (set.iFontH < 1)   set.iFontH = 1;
	if (set.iFontH > 32)  set.iFontH = 32;
	text.setCharacterSize(set.iFontH);
}

//  modifiers
void App::Mods(const sf::Event::KeyEvent& key)
{
	alt = key.alt;  ctrl = key.control;  shift = key.shift;

	//  multipliers
	dLine = alt ? 20 : ctrl ? 16 : shift ? 1 : 8;
	dFind = alt ? 8 : ctrl ? 4 : 1;
}

bool App::KeyUp(const sf::Event::KeyEvent& key)
{
	Mods(key);
}
