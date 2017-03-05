#include "list.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;


List::List()
{
}

void List::Default()
{
    pat.clear();
    clr.clear();

}

//  load, import from  DC doublecmd.xml
//------------------------------------------------
bool List::LoadFromDC(std::string file)
{
    Default();

    XMLDocument doc;
    doc.LoadFile(file.c_str());

    doc.RootElement();

    return true;
}

//  load, import from  TC color.ini
bool List::ImportFromTC(std::string file)
{
    Default();
    return true;
}


//  load project file, own
//------------------------------------------------
bool List::Load(std::string file)
{
    Default();

    XMLDocument doc;
    doc.LoadFile(file.c_str());

    doc.RootElement();

    return true;
}

//  save project file, own
bool List::Save(std::string file)
{
    XMLDocument doc;
    doc.SaveFile(file.c_str());
    return true;
}
