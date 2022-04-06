#pragma once

#include <memory>
#include "Messages.h"

/*
Usage		:  MessageConvert
Category	:  
Description :  Message를 알맞는 자료형으로 Convert해줌.
*/

class MessageConverter
{
private:
	std::shared_ptr<GameServerMessage> m_Message;
	const std::vector<unsigned char>& m_Buffer;
	
public: //Default
	MessageConverter(const std::vector<unsigned char>& _Buffer);

	EMessageType GetMessageType()
	{
		return m_Message->GetMessageType();
	}

	uint32_t GetMessageTypeByuint()
	{
		return static_cast<uint32_t>(GetMessageType());
	}

	std::shared_ptr<GameServerMessage> GetServerMessage()
	{
		return m_Message;
	}

	
};

