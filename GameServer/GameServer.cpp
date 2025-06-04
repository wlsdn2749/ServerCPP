#include "pch.h"
#include <iostream>

#include "SendBuffer.h"
#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
#include "tchar.h"
#include "Protocol.pb.h"
#include "Job.h"
#include "Room.h"
#include "Player.h"

// 패킷 직렬화 (Serialization)

//class Player
//{
//public:
//	int32 hp = 0;
//	int32 attack = 0;
//	Player* target = nullptr;
//	vector<int32> buffs;
//};

enum
{
	WORKER_TICK = 64
};
void DoWorkerJob(ServerServiceRef& service)
{
	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		// 네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러)
		service->GetIocpCore()->Dispatch(10);

		// 예약된 일감 처리
		ThreadManager::DistributeReservedJobs();

		// 글로벌 큐 (게임에서 처리되는 일감들을 처리함)
		ThreadManager::DoGlobalQueueWork();
	}
}

int main()
{
	GRoom->DoTimer(1000, [](){cout << "Hello 1000" << endl;});
	GRoom->DoTimer(2000, [](){cout << "Hello 2000" << endl;});
	GRoom->DoTimer(3000, [](){cout << "Hello 3000" << endl;});

	ClientPacketHandler::init();

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 8421),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO,  ()가 필요없는건, CreateSession으로 넘어가서 실행하기 때문
		100);

	ASSERT_CRASH(service->Start());
	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([&service]()
		{
			while (true)
			{
				// Worker Thread가 Queue에서 Event를 꺼냄
				//service->GetIocpCore()->Dispatch();
				DoWorkerJob(service);

			}
		});
	}

	DoWorkerJob(service);
	GThreadManager->Join();
}
