#ifndef LOG_INTERFACE_H_
#define LOG_INTERFACE_H_

#include <string>

enum LogLevel {
    kInfo,
    kDebug,
    kWarn,
    kError
};

class LogInterface {
public:
    virtual void DoLog(LogLevel level, 
        const std::string& tag, 
        const std::string& log) = 0;
};

#endif
