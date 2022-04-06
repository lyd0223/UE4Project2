#include "PreCompile.h"
#include "DBQueue.h"
#include <GameServerNet/DBConnecter.h>

std::mutex gDBConnectionRock;

//DB�� ������ ���ִ� �ݹ��Լ�.
void DBConnecterInitFunc(DBConnecter* _DBConnecter)
{
	//����Ŀ��Ʈ ȣ���� �����忡 ���������ʾ� ���� �ɾ���.
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

