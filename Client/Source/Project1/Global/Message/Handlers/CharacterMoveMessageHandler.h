#pragma once
#include "MessageHandlerBase.h"

class CharacterMoveMessageHandler : public MessageHandlerBase<CharacterMoveMessage>
{
public:
	void Start();
};
