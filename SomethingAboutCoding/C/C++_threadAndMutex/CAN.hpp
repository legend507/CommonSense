#include <string>

/*
This is a CANLogManager class (as a PoC in in-vehicle CAN Log Manager),
the process() listens to stdin and put data into sampleLog[10]
run() creates a thread and detach the thread (meaning let the thread run free)
*/
class CANLogManager {
public:
    std::string sampleLog[10];
    int index = 0;
    int process();
    int recordStr(std::string str);
    int print();
    int run();
};
