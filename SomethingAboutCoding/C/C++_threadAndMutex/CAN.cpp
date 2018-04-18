#include <iostream>
#include <thread>
#include <mutex>
#include "CAN.hpp"

std::mutex mtx;

int CANLogManager::run() {
    std::thread listen(&CANLogManager::process, this);
    listen.detach();    //如果不见这行，则会有runtime error；如果改成listen.join()，则不会有print，无法达成效果
    return 0x00;
}

int CANLogManager::process() {

    while(1) {
        mtx.lock();
        std::cout << "type something: ";
        mtx.unlock();        
        std::string str;
        std::cin >> str;
        
        recordStr(str);
    }

    return 0x00;
}

int CANLogManager::recordStr(std::string str) {

    sampleLog[index] = str;

    if(index == 9)  index = 0;
    else index++;

    return 0x00;
}

int CANLogManager::print() {
    mtx.lock();
    std::cout<<std::endl;
    std::cout << "---------------" << std::endl;
    for(int i = 0; i < 10; i++) {
        std::cout << sampleLog[i] << std::endl;
    }
    std::cout << "---------------" << std::endl;

    mtx.unlock();
    return 0x00;
}
