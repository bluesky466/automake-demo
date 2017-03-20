#include "easy_log.h"
#include "cout_log_interface.h"

int main()
{
    EasyLog log(std::make_shared<COutLogInterface>());
    log.Debug("test", "testlog");

    return 0;
}
