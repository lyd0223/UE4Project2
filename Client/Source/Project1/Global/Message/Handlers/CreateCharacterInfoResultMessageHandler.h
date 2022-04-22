#pragma once
#include "MessageHandlerBase.h"

class CreateCharacterInfoResultMessageHandler : public MessageHandlerBase<CreateCharacterInfoResultMessage>
{
public:
	virtual void Start() override;
	
};
