#pragma once
#include <GameServerBase/GameServerQueue.h>
/*
Usage		:  
Category	:  
Description :  DB관련업무를맡는다.
*/

class DBQueue
{

private: //Member Value
	static GameServerQueue m_JobQueue;
	
public: //Default
	DBQueue();
	~DBQueue();

	DBQueue(const DBQueue& _Other) = delete;
	DBQueue(DBQueue&& _Other)		noexcept;

protected:
	DBQueue& operator=(const DBQueue& _Other) = delete;
	DBQueue& operator=(DBQueue&& _Other)		= delete;

	
public:  //Member Function
	static void Initialize();
	static void EnQueue(const std::function<void()>& _CallBack);

	static void Destroy();
};

