#ifndef EASY_LOG_H_
#define EASY_LOG_H_

#include <iostream>
#include <memory>
#include <string>

#include "log_interface.h"

class EasyLog {
public:
    EasyLog(std::shared_ptr<LogInterface> interface);

    void Info(const std::string& tag, const std::string& log);

    void Debug(const std::string& tag, const std::string& log);

    void Warn(const std::string& tag, const std::string& log);

    void Error(const std::string& tag, const std::string& log);

private:
    std::string GetLog(const std::string& tag, const std::string& log) const;

    std::shared_ptr<LogInterface> interface_;
};

#endif
