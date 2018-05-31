#include "Logger.h"

#include <cstdio>
#include <ctime>

Logger& Log = Logger::GetInstance();

Logger::Logger()
{
    file = std::fopen("log.xml", "w");
    {
        time_t timer;
        char buff[64];

        std::time(&timer);
        auto tm_info = std::localtime(&timer);
        std::strftime(buff, 64, "<log time = \"%Y-%m-%d %H:%M:%S\">", tm_info);
        operator()(buff);
    }
}

Logger & Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

void Logger::operator()(char const * message)
{
    std::fputs(message, (std::FILE*)file);
    std::fputs("\n", (std::FILE*)file);
}

Logger::~Logger()
{
    operator()("</log>");
    std::fclose((std::FILE*)file);
}
