#pragma once
#include "MessageHandlerBase.h"
/*
Usage		:
Category	:
Description :  SaveCharacterInfo 패킷이 오면 처리해야할 동작을 구현.
*/



class SaveCharacterInfoMessageHandler : public MessageHandlerBase<SaveCharacterInfoMessage>
{
public:
	virtual void Start() override;

private:
	void DBCheck();

};

