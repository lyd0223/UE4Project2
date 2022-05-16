#pragma once
#include <memory>
#include "../Messages.h"

template<class MessageType>
class MessageHandlerBase
: std::enable_shared_from_this<MessageHandlerBase<MessageType>>
{
public:
	MessageHandlerBase()
	{
		m_GameInstance = nullptr;
		m_World = nullptr;
		m_Message = nullptr;
	}
	virtual ~MessageHandlerBase() {}

protected:
	class UWorld* m_World;
	class UProject1GameInstance* m_GameInstance;
	std::shared_ptr<MessageType> m_Message;

public:
	virtual void Init(UProject1GameInstance* _GameInstance,
		UWorld* _World, std::shared_ptr<MessageType> _Message)
	{
		m_GameInstance = _GameInstance;
		m_World = _World;
		m_Message = _Message;
	}

	//MessageHandler를 상속받는 클래스들이 무조건 가지도록 순수가상함수로 설정.
	virtual void Start() = 0;
};
