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

bool Config::Config::load()
{
    // Open input file
    this->file.open(path);
    this->path = path;

    if (! this->file.good()) {
        throw ReadException();
    }

    // Load data from file
    this->data->clear();
    std::string line;

    try {
        // Parse each line of config
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

bool Config::Config::isLoaded()
{
    return this->loaded;
}

void Config::Config::save()
{
    this->load();
}

void Config::Config::createNew()
{
    // If config file is already opened, close it
    if (this->isLoaded())
        this->file.close();

    // Creating new, empty file
    std::ofstream newfile(this->path, std::ios::out);
    newfile.close();

    // Load again
    this->load();
}

void Config::Config::setPath(std::string path)
{
    this->path = path;
}

std::string Config::Config::getPath()
{
    return this->path;
}

bool Config::Config::setAutosave(bool autosave)
{
    this->autosave = autosave;
}

bool Config::Config::getAutosaveSetting()
{
    return this->autosave;
}

