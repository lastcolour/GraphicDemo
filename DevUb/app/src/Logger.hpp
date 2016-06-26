#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iostream>
#include <fstream>
#include <memory>

class Logger {
public:

    ~Logger();

    static Logger& getInstance();

    void addFileStream(const char* fileaname);

    template<typename... Types>
    static void debug(const char* place, Types... args);

    template<typename... Types>
    static void error(const char* place, Types... args);

    template<typename... Types>
    static void info(const char* place, Types... args);

private:

    Logger();
    Logger(const Logger& logger);
    Logger& operator=(const Logger& logger);

    static void logMSG();

    template<typename T>
    static void logMSG(const T& message);

    template<typename T, typename... Types>
    static void logMSG(const T& message, Types... args);

private:

    std::ofstream fileStream;

};

template<typename T>
void Logger::logMSG(const T& message) {
    std::cout << message;
    if(getInstance().fileStream.is_open() && getInstance().fileStream.good()) {
       getInstance().fileStream << message;
    }
}

template<typename T, typename... Types>
void Logger::logMSG(const T& message, Types... args) {
    logMSG(message);
    logMSG(args...);
}

template<typename... Types>
void Logger::debug(const char* place, Types... args) {
    std::string tStr;
    tStr += "["; tStr += place; tStr += ":Debug] ";
    logMSG(tStr.c_str(), args...);
    logMSG();
}

template<typename... Types>
void Logger::error(const char* place, Types... args) {
    std::string tStr;
    tStr += "["; tStr += place; tStr += ":Error] ";
    logMSG(tStr.c_str(), args...);
    logMSG();
}

template<typename... Types>
void Logger::info(const char* place, Types... args) {
    std::string tStr;
    tStr += "["; tStr += place; tStr += ":Info] ";
    logMSG(tStr.c_str(), args...);
    logMSG();
}

#endif /* __LOGGER_HPP__ */
