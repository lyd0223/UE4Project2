#pragma once
#include "MessageHandlerBase.h"

class DeleteCharacterInfoResultMessageHandler : public MessageHandlerBase<DeleteCharacterInfoResultMessage>
{
public:
	virtual void Start() override;
	
};
