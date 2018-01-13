#include "include/Config/config.h"

Config::Config::Config()
{
    std::unique_ptr<std::map<std::string, std::string>> data(new std::map<std::string, std::string>);
    this->data = std::move(data);
}

Config::Config::~Config()
{
    this->file.close();
}

Config::Config&Config::Config::getInstance()
{
    static Config instance;
    return instance;
}

bool Config::Config::load(std::string path)
{
    // Open input file
    this->file.open(path);

    if (! this->file.good()) {
        throw ReadException();
    }

    // Load data from file
    this->data->clear();
    std::string line;

    try {
        while (std::getline(this->file, line)) {
            std::vector<std::string> iniEntry = Utils::explode(line, '=');
            this->data->insert(std::make_pair(iniEntry.at(0), iniEntry.at(1)));
        }
    } catch (...) {
        throw ReadException();
    }

    this->loaded = true;

    return true;
}

