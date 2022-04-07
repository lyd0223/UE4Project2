#pragma once
#include "MessageTypeEnum.h"
#include "ContentsEnum.h"
#include <GameServerBase/GameServerSerializer.h>

class GameServerMessage
{
public:
	GameServerMessage() = delete;
	GameServerMessage(EMessageType _MessageType)
	{
		m_MessageType = _MessageType;
		m_Size = -1;
	}

private:
	EMessageType m_MessageType;
	unsigned int m_Size;

public:
	EMessageType GetMessageType()
	{
		return m_MessageType;
	}

	virtual int SizeCheck() = 0
	{
		return -1;
	}

	int DataSizeCheck(const std::string& _Value)
	{
		return 4 + static_cast<int>(_Value.size());
	}
	template<class Type>
	int DataSizeCheck(Type _Value)
	{
		return sizeof(_Value);
	}

	virtual void Serialize(GameServerSerializer& _Serializer)
	{
		_Serializer << static_cast<unsigned int>(m_MessageType);
		_Serializer << SizeCheck();
	}
	
	virtual void DeSerialize(GameServerSerializer& _Serializer)
	{
		int Type = 0;
		_Serializer >> Type;
		m_MessageType = static_cast<EMessageType>(Type);
		_Serializer >> m_Size;
	}
};