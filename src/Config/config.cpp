#include "include/Config/config.h"

Config::Config::Config(std::string path)
{
    std::unique_ptr<std::map<std::string, std::string>> data(new std::map<std::string, std::string>);
    this->data = std::move(data);

    std::unique_ptr<std::fstream> file(new std::fstream());
    this->file = std::move(file);

    this->load(path);
}

Config::Config::~Config()
{

}

bool Config::Config::load(std::string path)
{
    // Open input file
    this->file->open(path);

    if (! this->file->good()) {
        throw ReadException();
    }

    // Load data from file
    this->data->clear();
    std::string line;
    while (std::getline(this->file, line)) {

    }

    return true;
}

