#pragma once
#include "MessageHandlerBase.h"
/*
Usage		:
Category	:
Description :  SaveCharacterInfo ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/



class SaveCharacterInfoMessageHandler : public MessageHandlerBase<SaveCharacterInfoMessage>
{
public:
	virtual void Start() override;

private:
	void DBCheck();

};

