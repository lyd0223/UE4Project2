#include "PreCompile.h"
#include "GameServerThread.h"
#include "GameServerDebug.h"

thread_local std::string GameServerThread::Name_;
thread_local unsigned int GameServerThread::Order_;
thread_local const std::type_info* GameServerThread::LocalDataTypeInfo_ = nullptr;
thread_local std::vector<char> GameServerThread::LocalData_;


GameServerThread::~GameServerThread() 
{

}

GameServerThread::GameServerThread(GameServerThread&& _Other) noexcept
{

}

void GameServerThread::join() 
{
	thread_.join();
}

