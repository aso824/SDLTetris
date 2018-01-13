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
#include "include/Config/writeexception.h"
#include "include/Logger/logger.h"

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

        void setAutosave(bool autosave = true);
        bool getAutosaveSetting();

        std::string getString(std::string key, std::string defaultValue = "");
        int getInt(std::string key, int defaultValue);
        float getFloat(std::string key, float defaultValue);
        bool getBoolean(std::string key, bool defaultValue);

        void setString(std::string key, std::string value);
        void setInt(std::string key, int value);
        void setFloat(std::string key, float value);
        void setBoolean(std::string key, bool value);

        std::vector<std::pair<std::string, std::string> > getAll();
        static void logDumpConfig();

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
