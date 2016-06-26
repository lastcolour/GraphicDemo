#include "Logger.hpp"

#include <cassert>

Logger::Logger() {
}

Logger::~Logger() {
}

Logger& Logger::getInstance() {
    // Mayers singleton
    static Logger logger;
    return logger;
}

void Logger::addFileStream(const char* fileaname) {
    assert(!fileStream.is_open() && "FileStream already exist");
    fileStream.open(fileaname);
    if(!fileStream.is_open()) {
        fileStream.clear();
        return;
    }
}

void Logger::logMSG() {
    std::cout << std::endl;
    if(getInstance().fileStream.is_open() && getInstance().fileStream.good()) {
        getInstance().fileStream << std::endl;
    }
}
