这个example是我在统合监视FW设计的时候想到的，
这个Example有两个class，一个中心管理class：CoreManager;一个CAN监视class：CANLogMaanger（为方便起见，这个class监视terminal的stdin）
CANLogManager是CoreManager的一个成员，其run()函数建立一个process()的thread
CoreManager的process()中，叫了CANLogManager的run(), 建立一个CANLogManager的process()的thread
    ，然后每隔10秒叫CANLogManager的print()

也在example中加入了一些mutex的用法，不过先要把thread学好，mutex可以无视
