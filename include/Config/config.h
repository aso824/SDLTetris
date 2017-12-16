#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>

#include "include/Config/readexception.h"

namespace Config {
    class Config
    {
    public:
        Config(std::string path = "");
        ~Config();

        bool load(std::string path);
        bool isLoaded();
        bool save(std::string path = "");
        std::string getPath();

        bool setAutosave(bool autosave = true);
        bool getAutosaveStatus();

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
        std::unique_ptr<std::fstream> file;
    };
}

#endif // CONFIG_H
