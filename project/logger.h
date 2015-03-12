#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

//log level
#define LOG_LEVEL 0
#define ERROR 0
#define WARNING 1
#define INFO 2
#define DEBUG 3

using namespace std;

class Logger
{
public:
    Logger();

    static void configLoggerLevel(int level);

    static void logError(string text);
    static void logWarning(string text);
    static void logInfo(string text);
    static void logDebug(string text);

private:
    static int level;
};

#endif // LOGGER_H
