#pragma once
#include "MessageTypeEnum.h"
#include "GameServerSerializer.h"


enum class ELoginResultType
{
	OK,
	Error,
	MAX
};

enum class ESignInResultType
{
	OK,
	Error_DuplicateID,
	Error_NonAvailableID,
	MAX
};
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
//
//class LoginMessage : public Message
//{
//private:
//	std::string m_ID;
//	std::string m_PW;
//
//public:
//	LoginMessage()
//		: Message(EMessageType::Login)
//	{
//		
//	}
//
//	public:
//	int SizeCheck() override
//	{
//		int size = DataSizeCheck(m_ID) + DataSizeCheck(m_PW);
//		return size;
//	}
//	
//	void SetID(std::string& _ID)
//	{
//		m_ID = _ID;
//	}
//	void SetPW(std::string& _PW)
//	{
//		m_PW = _PW;
//	}
//	
//	void Serialize(GameServerSerializer& _Serializer) override
//	{
//		Message::Serialize(_Serializer);
//		_Serializer << m_ID;
//		_Serializer << m_PW;
//	}
//
//	void DeSerialize(GameServerSerializer& _Serializer) override
//	{
//		Message::DeSerialize(_Serializer);
//		_Serializer >> m_ID;
//		_Serializer >> m_PW;
//	}
//};
//
//
//
//class LoginResultMessage : public Message
//{
//public:
//	ELoginResultType m_ResultType;
//	
//public:
//	LoginResultMessage()
//		:Message(EMessageType::LoginResult)
//	{
//		m_ResultType = ELoginResultType::MAX;
//	}
//	
//	int SizeCheck() override
//	{
//		return DataSizeCheck(m_ResultType);
//	}
//
//	void Serialize(GameServerSerializer& _Serializer) override
//	{
//		Message::Serialize(_Serializer);
//		_Serializer << static_cast<int>(m_ResultType);
//	}
//
//	void DeSerialize(GameServerSerializer& _Serializer) override
//	{
//		Message::DeSerialize(_Serializer);
//		_Serializer >> static_cast<int>(m_ResultType);
//	}
//};