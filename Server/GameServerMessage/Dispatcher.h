#pragma once
#include "Messages.h"
#include "GameServerNet/TCPSession.h"

/*
Usage		:
Category	:
Description :  서버로 날아온 패킷을 받으면 일을 처리하게해주는 클래스.
*/

template<class OWNER>
using MessageHandler = std::function<void(std::shared_ptr<OWNER>, std::shared_ptr<GameServerMessage>)>;

template<class OWNER>
class Dispatcher
{

private:
	std::unordered_map<uint32_t, MessageHandler<OWNER>> m_HandlersMap;

public: //Default
	Dispatcher()
	{

	}
	~Dispatcher()
	{

	}


	bool AddHandler(uint32_t _MessageType, const MessageHandler<OWNER> _Handler)
	{
		auto Result = m_HandlersMap.insert(std::make_pair(_MessageType, _Handler));
		return Result.second;
	}
	bool GetHandler(uint32_t _ID, MessageHandler<OWNER>& _Handler)
	{
		auto Iter = m_HandlersMap.find(_ID);
		if (Iter == m_HandlersMap.end())
		{
			return false;
		}
		_Handler = Iter->second;

		return true;
	}


private: //Member Value


public:  //Member Function
};
