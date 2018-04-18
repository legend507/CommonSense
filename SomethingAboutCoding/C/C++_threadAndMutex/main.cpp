#include <iostream>
#include <unistd.h>
#include <thread>
#include "CAN.hpp"

/*
CoreManager class is a center log manager,
it has CANLogManager clm as a child,
in process(), clm.run() starts a thread to listen stdin,
and in the while(1) loop, the clm print data in every 5 seconds
*/
class CoreManager{
public:
    CANLogManager clm;

    int process() {
        clm.run();      // this line created a new thread

        while(1) {
            clm.print();
            sleep(5);
        }
        return 0x00;
    }

};

int main() {
    CoreManager cm;

    cm.process();    

    return 0x00;
}
