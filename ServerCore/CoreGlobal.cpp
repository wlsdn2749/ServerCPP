#include "pch.h"
#include "CoreGlobal.h"

#include "DeadLockProfiler.h"
#include "ThreadManager.h"
#include "Memory.h"

ThreadManager*			GThreadManager = nullptr;
DeadLockProfiler*		GDeadLockProfiler = nullptr;
Memory*					GMemory = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GThreadManager = new ThreadManager(); // 여기서 스레드를 하나 생성
		GMemory = new Memory();
		GDeadLockProfiler = new DeadLockProfiler();
	}
	~CoreGlobal()
	{
		delete GThreadManager;
		delete GMemory;
		delete GDeadLockProfiler;
	}
private:

} GCoreGlobal;

