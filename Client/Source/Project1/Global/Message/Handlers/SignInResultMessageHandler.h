#pragma once
#include <memory>
#include "MessageHandlerBase.h"

class SignInResultMessageHandler : public MessageHandlerBase<SignInResultMessage>
{

public:
	virtual void Start() override;
};
