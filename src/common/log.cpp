#include "log.h"

#include "common/log.h"
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>

#include <plog/Appenders/ColorConsoleAppender.h>        // for command prompt log purpose
#include <plog/Appenders/RollingFileAppender.h>

int InitLogger()
{
    static auto appender = plog::ColorConsoleAppender<plog::TxtFormatterImpl<false>>();
#if _DEBUG
    plog::init(plog::debug, &appender);
#else
    plog::init(plog::info, &appender);
#endif
    /*
    char buf[128] = { 0 };
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    strftime(buf, sizeof(buf), "%F", std::gmtime(&t));
    std::stringstream logfile;
    logfile << PROJECT_NAME << "-" << buf << ".log";
    static auto txtAppender = plog::RollingFileAppender<plog::TxtFormatterImpl<false>>{ logfile.str().c_str(), 1000000, 5 };
    plog::init(plog::info, &txtAppender);
    */
    return 0;
}

int FreeLogger()
{
    return 0;
}