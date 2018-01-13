#include "include/Config/config.h"

Config::Config::Config()
{
    std::unique_ptr<std::map<std::string, std::string>> data(new std::map<std::string, std::string>);
    this->data = std::move(data);
}

Config::Config::~Config()
{
    this->file.flush();
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
            if (line.empty())
                continue;

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
    // Unload already loaded config
    if (this->isLoaded()) {
        this->file.close();
        this->loaded = false;
    }

    // Creating new, empty file
    try {
        std::ofstream writeStream(this->path, std::ios::out | std::ios::trunc);

        std::map<std::string, std::string>::const_iterator it;

        for (it = this->data->begin(); it != this->data->end(); ++it) {
            writeStream << it->first
                       << "="
                       << it->second
                       << std::endl;
        }

        writeStream.close();
    } catch (...) {
        throw WriteException();
    }

    // Load again
    this->load();
}

void Config::Config::createNew()
{
    // If config file is already opened, close it
    if (this->isLoaded()) {
        this->file.close();
        this->loaded = false;
    }

    // Creating new, empty file
    try {
        std::ofstream newfile(this->path, std::ios::out);
        newfile.close();
    } catch (...) {
        throw WriteException();
    }

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

void Config::Config::setAutosave(bool autosave)
{
    this->autosave = autosave;
}

bool Config::Config::getAutosaveSetting()
{
    return this->autosave;
}

std::string Config::Config::getString(std::string key, std::string defaultValue)
{
    std::map<std::string, std::string>::const_iterator it = this->data->find(key);

    if (it == this->data->end()) {
        this->data->insert(std::make_pair(key, defaultValue));

        if (this->autosave) {
            this->save();
        }

        return defaultValue;
    }

    return it->second;
}

int Config::Config::getInt(std::string key, int defaultValue)
{
    std::string val = this->getString(key, std::to_string(defaultValue));

    return atoi(val.c_str());
}

float Config::Config::getFloat(std::string key, float defaultValue)
{
    std::string val = this->getString(key, std::to_string(defaultValue));

    return atof(val.c_str());
}

void Config::Config::setString(std::string key, std::string value)
{
    std::map<std::string, std::string>::iterator it = this->data->find(key);

    if (it == this->data->end()) {
        this->data->insert(std::make_pair(key, value));
    } else {
        it->second = value;
    }

    if (this->autosave) {
        this->save();
    }
}

void Config::Config::setInt(std::string key, int value)
{
    this->setString(key, std::to_string(value));
}

void Config::Config::setFloat(std::string key, float value)
{
    this->setString(key, std::to_string(value));
}

std::vector<std::pair<std::string, std::string> > Config::Config::getAll()
{
    std::vector<std::pair<std::string, std::string> > result;

    for (auto it = this->data->begin(); it != this->data->end(); ++it) {
        result.push_back(*it);
    }

    return result;
}

void Config::Config::logDumpConfig()
{
    Logger::Logger::debug("Dumping all config keys and values:");

    std::vector<std::pair<std::string, std::string> > data = Config::Config::getInstance().getAll();

    for (size_t i = 0; i < data.size(); i++) {
        Logger::Logger::debug(data[i].first + ": " + data[i].second);
    }
}

