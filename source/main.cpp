#include "AppMain.h"
#include <locale.h>
#include <cstdlib>
#include <memory>
using namespace std; 


//  . . . . . . . . . . . . . . . . . . . . . .  MAIN  . . . . . . . . . . . . . . . . . . . . . .
int main()
{
	setlocale(LC_NUMERIC, "C");

	//  Start
	//-----------------------------------

	unique_ptr<AppMain> pApp = make_unique<AppMain>();

	pApp->Run();


	return EXIT_SUCCESS;
}
