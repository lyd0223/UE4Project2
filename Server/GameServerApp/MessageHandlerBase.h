#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

template<class MessageType>
class MessageHandlerBase : public std::enable_shared_from_this<MessageHandlerBase<MessageType>>
{
protected:
	//패킷을 보낸 세션
	std::shared_ptr<TCPSession> m_TCPSession;
	//온 패킷
	std::shared_ptr<MessageType> m_Message;


public: //Default
	MessageHandlerBase() 
	{
		m_TCPSession = nullptr;
		m_Message = nullptr;
	}
	virtual ~MessageHandlerBase() {}

	MessageHandlerBase(const MessageHandlerBase& _Other) = delete;
	MessageHandlerBase(MessageHandlerBase&& _Other)		noexcept = delete;
	MessageHandlerBase& operator=(const MessageHandlerBase& _Other) = delete;
	MessageHandlerBase& operator=(MessageHandlerBase&& _Other) = delete;


public:
	void Init(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<MessageType> _Message)
	{
		m_TCPSession = _TCPSession;
		m_Message = _Message;
	
	}
	//메시지 받았을때 실행하는 함수. 순수가상함수.
	virtual void Start() = 0;

};

