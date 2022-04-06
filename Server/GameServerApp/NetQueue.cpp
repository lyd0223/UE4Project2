#include "PreCompile.h"
#include "NetQueue.h"

GameServerQueue NetQueue::m_JobQueue = GameServerQueue();

NetQueue::NetQueue()
{

}

NetQueue::~NetQueue()
{

}

NetQueue::NetQueue(NetQueue&& _Other) noexcept
{

}

void NetQueue::Initialize()
{
	m_JobQueue.Initialize(GameServerQueue::WORK_TYPE::Default, 20, "NetThread");
}

void NetQueue::EnQueue(const std::function<void()>& _CallBack)
{
	m_JobQueue.EnQueue(_CallBack);
}

void NetQueue::Destroy()
{
	m_JobQueue.Destroy();
}