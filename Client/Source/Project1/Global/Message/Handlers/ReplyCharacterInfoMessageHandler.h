#pragma once
#include "MessageHandlerBase.h"

class ReplyCharacterInfoMessageHandler : public MessageHandlerBase<ReplyCharacterInfoMessage>
{
public:
	virtual void Start() override;
	
};
