//  Original file comes from Stunt Rally (pathmanager.cpp),
//  under GPLv3, http://stuntrally.tuxfamily.org/
//  which came from Performous, under GPL, http://performous.org
//  It now uses C++17 and no Boost

#include "FileSystem.h"
#include <algorithm>
#include <iostream>
using namespace std;

#include <string>
#include <fstream>
#include <list>
#include <cassert>
#include <sstream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif

//  const
#define DATA_DIR "data"
#define APP_NAME "ccc"

#include <filesystem>
namespace fs = std::filesystem;


//  static vars
string FileSystem::home_dir
    ,FileSystem::user_config
    ,FileSystem::app_data;


//  List dir
//-------------------------------------------------
vector<fs::path> FileSystem::ListDir(const fs::path dir)
{
    vector<fs::path> files;
    try
    {
        auto it = fs::recursive_directory_iterator(dir);
        for (const auto& path: it)
            files.push_back(path);

		sort(files.begin(), files.end());
    }
    catch (exception ex)
    {
        cerr << ex.what() << endl;
    }
    return files;
}


bool FileSystem::Exists(const string& filename)
{
    return fs::exists(filename);
}

bool FileSystem::CreateDir(const string& path)
{
    try	{	fs::create_directories(path);	}
    catch (...)
    {
        cerr << "Could not create directory " << path << endl;
        return false;
    }
    return true;
}


// Print diagnostic info  ----
string FileSystem::GetInfo()
{
    string s;
    s += "Paths info\n";
    s += "-------------------------\n";
    s += "Data:    " + Data() + "\n";
    s += "Home:    " + home_dir + "\n";
    s += "Config:  " + Config() + "\n";
    //s += "User data:    " + user_data + "\n";
    //s += "Cache:        " + Cache() + "\n";
    s += "-------------------------\n";
    return s;
}


//  Init
///---------------------------------------------------------------------------------------------------
void FileSystem::Init()
{
    fs::path appname = APP_NAME;

    // Figure out user's home directory  ----
    {
        home_dir = "";
        #ifndef _WIN32 // POSIX
            char *homedir = getenv("HOME");
            if (homedir == nullptr)
            {
                home_dir = "/home/";
                homedir = getenv("USER");
                if (homedir == nullptr) {
                    homedir = getenv("USERNAME");
                    if (homedir == nullptr) {
                        cerr << "Could not find user's home directory!" << endl;
                        home_dir = "/tmp/";
                    }
                }
            }
        #else // Windows
            char *homedir = getenv("USERPROFILE");
            if (homedir == NULL) homedir = "data"; // WIN 9x/Me
        #endif
        home_dir += homedir;
    }

    // Find user's config dir  ----
    #ifndef _WIN32 // POSIX
    {
        char const* conf = getenv("XDG_CONFIG_HOME");
        if (conf) user_config = (fs::path(conf) / appname).string();
        else user_config = (fs::path(home_dir) / ".config" / appname).string();
    }
    #else // Windows
    {
        // Open AppData directory
        string str;
        ITEMIDLIST* pidl;
        char AppDir[MAX_PATH];
        HRESULT hRes = SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA|CSIDL_FLAG_CREATE, &pidl);
        if (hRes == NOERROR)
        {
            SHGetPathFromIDList(pidl, AppDir);
            int i;
            for (i = 0; AppDir[i] != '\0'; ++i) {
                if (AppDir[i] == '\\') str += '/';
                else str += AppDir[i];
            }
            user_config = (fs::path(str) / appname).string();
        }
    }
    #endif

    // Create user's config dir  ----
    CreateDir(user_config);

    // Find user's data dir (for additional data)
    /*#ifdef _WIN32
    user_data = user_config;  // APPDATA/appname
    #else
    {
        char const* xdg_data_home = getenv("XDG_DATA_HOME");
        user_data = (xdg_data_home ? xdg_data_home / appname
                    : fs::path(home_dir) / ".local/share" / appname).string();
    }
    #endif*/

    // Create user's data dir and its children
    ///--------------------------------------------------
    //CreateDir(user_data);
    //CreateDir(Screenshots());


    // Find app data dir and defaults config dir
    char *datadir = getenv("CCC_DATA_ROOT");
    if (datadir)
        app_data = string(datadir);
    else
    {	fs::path shareDir = DATA_DIR;
        vector<fs::path> dirs;

        // Adding relative path for running from sources
        fs::path exe = ExecName();
        dirs.push_back(exe.parent_path().parent_path() / "data");
        dirs.push_back(exe.parent_path().parent_path());
        dirs.push_back(exe.parent_path() / "data");
        dirs.push_back(exe.parent_path());
        // Adding relative path from installed executable
        dirs.push_back(exe.parent_path().parent_path() / shareDir);
        #ifndef _WIN32
        // Adding XDG_DATA_DIRS
        {
            char const* xdg_data_dirs = getenv("XDG_DATA_DIRS");
            istringstream iss(xdg_data_dirs ? xdg_data_dirs : "/usr/local/share/:/usr/share/");
            for (string p; getline(iss, p, ':'); dirs.push_back(p / appname)) {}
        }
        #endif

        //  Loop through the paths and pick the first one that contain some data
        for (const auto& p: dirs)
        {
            //  Data dir
            if (fs::exists(p / "icon.png"))  // subdir in data/
            //if (fs::exists(p))
                app_data = p.string();

            //  Check if found
            if (!app_data.empty())
                break;
        }
    }


    // Find cache dir  ----
    /*#ifdef _WIN32
    cache_dir = user_config + "/cache";  // APPDATA/appname/cache
    #else
    char const* xdg_cache_home = getenv("XDG_CACHE_HOME");
    cache_dir = (xdg_cache_home ? xdg_cache_home / appname
                : fs::path(home_dir) / ".cache" / appname).string();
    #endif*/

    // Create cache dir
    //CreateDir(CacheDir());
}
///---------------------------------------------------------------------------------------------------


//  Get the current executable name with path.
//  Returns empty path if the name cannot be found.
//  May return absolute or relative paths.

#if defined(_WIN32)
    #include <windows.h>
    fs::path FileSystem::ExecName()
    {
        char buf[1024];
        DWORD ret = GetModuleFileName(NULL, buf, sizeof(buf));
        if (ret == 0 || ret == sizeof(buf)) return fs::path();
        return buf;
    }
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    fs::path FileSystem::ExecName()
    {
        char buf[1024];
        uint32_t size = sizeof(buf);
        int ret = _NSGetExecutablePath(buf, &size);
        if (ret != 0) return fs::path();
        return buf;
    }
#elif defined(sun) || defined(__sun)
    #include <stdlib.h>
    fs::path FileSystem::ExecName()
    {
        return getexecname();
    }
#elif defined(__FreeBSD__)
    #include <sys/sysctl.h>
    fs::path FileSystem::ExecName()
    {
        int mib[4];
        mib[0] = CTL_KERN;
        mib[1] = KERN_PROC;
        mib[2] = KERN_PROC_PATHNAME;
        mib[3] = -1;
        char buf[1024];
        size_t maxchars = sizeof(buf) - 1;
        size_t size = maxchars;
        sysctl(mib, 4, buf, &size, NULL, 0);
        if (size == 0 || size >= maxchars) return fs::path();
        buf[size] = '\0';
        return buf;
    }
#elif defined(__linux__)
    #include <unistd.h>
    fs::path FileSystem::ExecName()
    {
        char buf[1024];
        ssize_t maxchars = sizeof(buf) - 1;
        ssize_t size = readlink("/proc/self/exe", buf, sizeof(buf));
        if (size <= 0 || size >= maxchars) return fs::path();
        buf[size] = '\0';
        return buf;
    }
#else
    fs::path FileSystem::ExecName()
    {
        return fs::path();
    }
#endif
