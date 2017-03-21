#include "easy_log.h"

using namespace std;

EasyLog::EasyLog(shared_ptr<LogInterface> interface)
    : interface_(interface)
{
}

void EasyLog::Info(const string& tag, const string& log)
{
    interface_->DoLog(kInfo, tag, GetLog(tag, log));
}

void EasyLog::Debug(const string& tag, const string& log)
{
    interface_->DoLog(kDebug, tag, GetLog(tag, log));
}

void EasyLog::Warn(const string& tag, const string& log)
{
    interface_->DoLog(kWarn, tag, GetLog(tag, log));
}

void EasyLog::Error(const string& tag, const string& log)
{
    interface_->DoLog(kError, tag, GetLog(tag, log));
}

std::string EasyLog::GetLog(const string& tag, const string& log) const
{
    return "[" + tag + "]" + " " + log;
}
