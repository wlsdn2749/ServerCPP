#include "pch.h"
#include "CoreGlobal.h"

#include "DeadLockProfiler.h"
#include "GlobalQueue.h"
#include "ThreadManager.h"
#include "Memory.h"
#include "SocketUtils.h"
#include "SendBuffer.h"
#include "JobTimer.h"
#include "DBConnectionPool.h"

ThreadManager*			GThreadManager = nullptr;
DeadLockProfiler*		GDeadLockProfiler = nullptr;
Memory*					GMemory = nullptr;
SendBufferManager*		GSendBufferManager = nullptr;
GlobalQueue*			GGlobalQueue = nullptr;
JobTimer*				GJobTimer = nullptr;
DBConnectionPool*		GDBConnectionPool = nullptr;



class CoreGlobal
{
public:
	CoreGlobal()
	{
		GThreadManager = new ThreadManager(); // 여기서 스레드를 하나 생성
		GMemory = new Memory();
		GSendBufferManager = new SendBufferManager();
		GDeadLockProfiler = new DeadLockProfiler();
		GGlobalQueue = new GlobalQueue();
		GJobTimer = new JobTimer();
		GDBConnectionPool = new DBConnectionPool();
		SocketUtils::Init();
	}
	~CoreGlobal()
	{
		delete GThreadManager;
		delete GMemory;
		delete GSendBufferManager;
		delete GDeadLockProfiler;
		delete GGlobalQueue;
		delete GJobTimer;
		delete GDBConnectionPool;
		SocketUtils::Clear();
	}
private:

} GCoreGlobal;

