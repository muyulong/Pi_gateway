#ifndef SYSTEM_H
#define SYSTEM_H

#include "log.h"

class system
{
public:
    system();
    ~system();

    void initSystem();
    void initDevices();
    void checkTasks();
    //void getDevicesInfo();
    //void getOperableDevices();
    void commandEncode(QString msg);
    //void commandDecode(δ֪����);
    //void commandSend(δ֪����);
    //void commandReceive();




    private:
    class log L;

};




#endif // SYSTEM_H
