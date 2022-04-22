#pragma once
#include "MessageHandlerBase.h"

class ChatMessageHandler : public MessageHandlerBase<ChatMessage>
{
public:
	void Start();
};
