#pragma once
#include <memory>
#include <map>
#include <functional>
#include "Messages.h"

// OWNER 이 패킷을 받은 세션
using  MessageHandler = std::function<void(std::shared_ptr<GameServerMessage>)>;

// 이 메세지 디스패처의 역할은
//    이렇게 다양한 쓰레드를 넘나들고
//    많은 단계를 거쳐야하는 일을
//    하나의 클래스에서 확인할수 있게 해주는 용도.

class Dispatcher
{

private: // Member Var
	std::map<unsigned int, MessageHandler> m_HandlerMap;

public: // Default
	Dispatcher() {}
	~Dispatcher() {}

	bool AddHandler(EMessageType _MessageType, const MessageHandler _Handler)
	{
		return AddHandler(static_cast<unsigned int>(_MessageType), _Handler);
	}

	bool AddHandler(unsigned int _MessageType, const MessageHandler _Handler)
	{
		m_HandlerMap.insert(std::make_pair(_MessageType, _Handler));

		return true;
	}

	// int* TMap.find

	bool GetHandler(EMessageType _MessageType, MessageHandler& _Handler) 
	{
		return GetHandler(static_cast<unsigned int>(_MessageType), _Handler);
	}

	bool GetHandler(uint32_t _MessageType, MessageHandler& _Handler) 
	{
		auto FindData = m_HandlerMap.find(_MessageType);

		if (m_HandlerMap.end() == FindData)
		{
			return false;
		}

		// _Handler = *FindData;

		_Handler = FindData->second;

		return true;
	}


public: // Member Function
};

