#pragma once
#include <GameServerBase/GameServerQueue.h>
/*
Usage		:  모든 클래스 기본.  
Category	:  Object 
Description :  오브젝트 상속용.
*/

class NetQueue
{
private: //Member Value
	static GameServerQueue m_JobQueue;

public: //Default
	NetQueue();
	~NetQueue();

	NetQueue(const NetQueue& _Other) = delete;
	NetQueue(NetQueue&& _Other)		noexcept;

	static GameServerQueue& GetQueue()
	{
		return m_JobQueue;
	}

protected:
	NetQueue& operator=(const NetQueue& _Other) = delete;
	NetQueue& operator=(NetQueue&& _Other) = delete;


public:  //Member Function
	static void Initialize();

	static void EnQueue(const std::function<void()>& _CallBack);

	static void Destroy();
};

