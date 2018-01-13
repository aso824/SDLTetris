#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

#include "include/utils.h"
#include "include/Config/readexception.h"

namespace Config {
    class Config
    {
    public:
        ~Config();
        static Config& getInstance();

        bool load();
        bool isLoaded();
        void save();
        void createNew();

        void setPath(std::string path);
        std::string getPath();

        bool setAutosave(bool autosave = true);
        bool getAutosaveSetting();

        std::string getString(std::string key);
        int getInt(std::string key);
        float getFloat(std::string key);

        void setString(std::string key, std::string value);
        void setInt(std::string key, int value);
        void setFloat(std::string key, float value);

    protected:
        std::string path;
        bool loaded = false;
        bool autosave = false;

        std::unique_ptr<std::map<std::string, std::string>> data;
        std::fstream file;

        Config();
    };
}

#endif // CONFIG_H
