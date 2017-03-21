#include "cout_log_interface.h"
#include <iostream>

using namespace std;

void COutLogInterface::DoLog(LogLevel level, 
        const string& tag, 
        const string& log) {
    cout<<log<<endl;
}
