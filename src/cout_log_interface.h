#ifndef COUT_LOG_INTERFACE_H_
#define COUT_LOG_INTERFACE_H_

#include "log_interface.h"

class COutLogInterface : public LogInterface {
public:
    virtual void DoLog(LogLevel level, 
        const std::string& tag, 
        const std::string& log);
};

#endif
