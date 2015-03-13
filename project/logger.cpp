#include "logger.h"

int Logger::level = 0;

Logger::Logger()
{
}

void Logger::configLoggerLevel(int level)
{
    Logger::level=level;
    cout<<"Set logger level to "<<level<<endl;
}

void Logger::logError(string text)
{
    if(level>=ERROR)
        cout<<"ERROR - "<<text<<endl;
}

void Logger::logWarning(string text)
{
    if(level>=WARNING)
        cout<<"WARN - "<<text<<endl;
}

void Logger::logInfo(string text)
{
    if(level>=INFO)
        cout<<"INFO - "<<text<<endl;
}

void Logger::logDebug(string text)
{
    if(level>=DEBUG)
        cout<<"DEBUG - "<<text<<endl;
}
