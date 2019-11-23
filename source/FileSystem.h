#pragma once
#include <vector>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;


class FileSystem
{
private:
    static std::string
        home_dir, user_config,
        app_data/*, user_data, cache_dir*/;

public:
    //  File system utility  ----

    //  List files and subdirs in path
    static std::vector<fs::path> ListDir(const fs::path start);

    static bool Exists(const std::string & filename);

    static bool CreateDir(const std::string& path);

    static fs::path ExecName();  // application path


    //  Call first to have paths  ----
    static void Init();

    static std::string GetInfo();

    //  Paths
    static std::string Home() {         return home_dir; }

    static std::string Config() {       return user_config;  }
    
    //static std::string Cache() {      return cache_dir; }

    //static std::string Settings() {     return user_config + "/ccc.xml"; }

    static std::string Data() {         return app_data; }

    //static std::string Screenshots() {  return user_data + "/screenshots";  }
};
