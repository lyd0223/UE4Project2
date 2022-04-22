#pragma once
#include <memory>
#include "MessageHandlerBase.h"

class ServerDestroyMessageHandler : public MessageHandlerBase<ServerDestroyMessage>
{
public:
	virtual void Start() override;
};
