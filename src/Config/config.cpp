#include "include/Config/config.h"

/**
 * @brief Ctor
 */
Config::Config::Config()
{
    std::unique_ptr<std::map<std::string, std::string>> data(new std::map<std::string, std::string>);
    this->data = std::move(data);
}

/**
 * @brief Dtor
 */
Config::Config::~Config()
{
    if (this->exitSave && this->modified) {
        this->save();
    }

    this->file.flush();
    this->file.close();
}

/**
 * @brief Main method for singleton
 * @return Static Config instance
 */
Config::Config&Config::Config::getInstance()
{
    static Config instance;
    return instance;
}

/**
 * @brief Perform config file loading and parsing
 * @return true if config get loaded
 * @throws ReadException when file could not be opened or content is invalid
 */
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

/**
 * @brief Tells if config file is already loaded, based on internal boolean
 * @return Config file load status
 */
bool Config::Config::isLoaded()
{
    return this->loaded;
}

/**
 * @brief Saves config data into file
 * @throws WriteException when any write error occured
 */
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

/**
 * @brief Creates new config file or resets already existing/loaded config file
 * @throws WriteException when any write error occured
 */
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

/**
 * @brief Set filename or path of config file, relative to executable directory
 * @param File path / name to be set
 */
void Config::Config::setPath(std::string path)
{
    this->path = path;
}

/**
 * @brief Get currently set config filepath
 * @return Config file path
 */
std::string Config::Config::getPath()
{
    return this->path;
}

/**
 * @brief Set status of autosave function
 * @param autosave Autosave function status
 */
void Config::Config::setAutosave(bool autosave)
{
    this->autosave = autosave;
}

/**
 * @brief Gets status of autosave function
 * @return Autosave function status
 */
bool Config::Config::getAutosaveSetting()
{
    return this->autosave;
}

/**
 * @brief Sets status of exit save function
 * @param exit Save Exit save function status
 */
void Config::Config::setExitSave(bool exitSave)
{
    this->exitSave = exitSave;
}

/**
 * @brief Gets status of exit save function
 * @return Exit save function status
 */
bool Config::Config::getExitSaveSetting()
{
    return this->exitSave;
}

/**
 * @brief Tells if config data has been modified by get or set functions
 * @return True if data has been modified
 */
bool Config::Config::hasModified()
{
    return this->modified;
}

/**
 * @brief Get string from config by key
 * @param key Name of value to fetch
 * @param defaultValue Value to be returned by function if key not found
 * @return Value found or from default parameter
 */
std::string Config::Config::getString(std::string key, std::string defaultValue)
{
    std::map<std::string, std::string>::const_iterator it = this->data->find(key);

    if (it == this->data->end()) {
        this->data->insert(std::make_pair(key, defaultValue));

        this->modified = true;

        if (this->autosave) {
            this->save();
        }

        return defaultValue;
    }

    return it->second;
}

/**
 * @brief Get int from config by key
 * @param key Name of value to fetch
 * @param defaultValue Value to be returned by function if key not found
 * @return Value found or from default parameter
 */
int Config::Config::getInt(std::string key, int defaultValue)
{
    std::string val = this->getString(key, std::to_string(defaultValue));

    return atoi(val.c_str());
}

/**
 * @brief Get float from config by key
 * @param key Name of value to fetch
 * @param defaultValue Value to be returned by function if key not found
 * @return Value found or from default parameter
 */
float Config::Config::getFloat(std::string key, float defaultValue)
{
    std::string val = this->getString(key, std::to_string(defaultValue));

    return atof(val.c_str());
}

/**
 * @brief Get boolean from config by key
 * @param key Name of value to fetch
 * @param defaultValue Value to be returned by function if key not found
 * @return Value found or from default parameter
 */
bool Config::Config::getBoolean(std::string key, bool defaultValue)
{
    std::string val = this->getString(key, std::to_string(defaultValue));

    if (val == "1" || val == "true" || val == "TRUE") {
        return true;
    }

    return false;
}

/**
 * @brief Sets config key and value in config data
 * @param key Name for value to be set
 * @param value Value to be set
 */
void Config::Config::setString(std::string key, std::string value)
{
    std::map<std::string, std::string>::iterator it = this->data->find(key);

    if (it == this->data->end()) {
        this->data->insert(std::make_pair(key, value));

        this->modified = true;
    } else {
        it->second = value;
    }

    if (this->autosave) {
        this->save();
    }
}

/**
 * @brief Sets config key and value in config data
 * @param key Name for value to be set
 * @param value Value to be casted to string and set
 */
void Config::Config::setInt(std::string key, int value)
{
    this->setString(key, std::to_string(value));
}

/**
 * @brief Sets config key and value in config data
 * @param key Name for value to be set
 * @param value Value to be casted to string and set
 */
void Config::Config::setFloat(std::string key, float value)
{
    this->setString(key, std::to_string(value));
}

/**
 * @brief Sets config key and value in config data
 * @param key Name for value to be set
 * @param value Value to be casted to string and set
 */
void Config::Config::setBoolean(std::string key, bool value)
{
    this->setInt(key, value);
}

/**
 * @brief Get all config keys and values in vector
 * @return Vector of pairs with keys and values, sorted alphabetically by key
 */
std::vector<std::pair<std::string, std::string> > Config::Config::getAll()
{
    std::vector<std::pair<std::string, std::string> > result;

    for (auto it = this->data->begin(); it != this->data->end(); ++it) {
        result.push_back(*it);
    }

    return result;
}

/**
 * @brief Dumps all keys and values into console with DEBUG level
 */
void Config::Config::logDumpConfig()
{
    Logger::Logger::debug("Dumping all config keys and values:");

    std::vector<std::pair<std::string, std::string> > data = Config::Config::getInstance().getAll();

    for (size_t i = 0; i < data.size(); i++) {
        Logger::Logger::debug(data[i].first + ": " + data[i].second);
    }
}

