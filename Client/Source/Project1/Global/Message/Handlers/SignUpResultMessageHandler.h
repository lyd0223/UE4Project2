#pragma once
#include <memory>
#include "MessageHandlerBase.h"

class SignUpResultMessageHandler : public MessageHandlerBase<SignUpResultMessage>
{
public:
	virtual void Start() override;
	
};
