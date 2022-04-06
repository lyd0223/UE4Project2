#include "PreCompile.h"
#include "DBQueue.h"
#include <GameServerNet/DBConnecter.h>

std::mutex gDBConnectionRock;

//DB와 연결을 해주는 콜백함수.
void DBConnecterInitFunc(DBConnecter* _DBConnecter)
{
	//리얼커넥트 호출은 스레드에 안전하지않아 락을 걸었다.
	gDBConnectionRock.lock();
	
	if (_DBConnecter == nullptr)
	{
		GameServerDebug::AssertDebugMsg("DBConnecter is nullptr");
		gDBConnectionRock.unlock();
		return;
	}

	if (_DBConnecter->Connect("127.0.0.1", "root", "1234", "unrealserver", 3306) == false)
	{
		std::string ErrorString = _DBConnecter->GetLastErrorStr();
		GameServerDebug::AssertDebugMsg("DBConnect Failed" + ErrorString);
		gDBConnectionRock.unlock();
		return; 
	}

	gDBConnectionRock.unlock();
}


GameServerQueue DBQueue::m_JobQueue = GameServerQueue();

DBQueue::DBQueue()
{

}

DBQueue::~DBQueue()
{

}

DBQueue::DBQueue(DBQueue&& _Other) noexcept
{

}

void DBQueue::Initialize()
{
	m_JobQueue.LocalDataInitialize<DBConnecter>(GameServerQueue::WORK_TYPE::Default, 20, "DBThread", DBConnecterInitFunc);
}

void DBQueue::EnQueue(const std::function<void()>& _CallBack)
{
	m_JobQueue.EnQueue(_CallBack);
}

void DBQueue::Destroy()
{
	m_JobQueue.Destroy();
}

