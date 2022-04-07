#pragma once																									  
#include "CoreMinimal.h"																						  
#include <functional>																								
#include "../Dispatcher.h"																						
																												  
#include "SignInResultMessageHandler.h"
#include "ServerDestroyMessageHandler.h"
#include "SignUpResultMessageHandler.h"
#include "ChatMessageHandler.h"
																												  
template<class MessageHandler, class MessageType>															  
void OnMessageProcess(std::shared_ptr<GameServerMessage> _Message, class UProject1GameInstance* _Inst, UWorld* _World)	  
{																												  
	std::shared_ptr<MessageType> ConvertMessage = std::static_pointer_cast<MessageType>(_Message);				  
	if (nullptr == ConvertMessage)																				  
	{																											  
		return;																									  
	}																											  
																												  
	MessageHandler Cmd = MessageHandler(ConvertMessage);														  
	Cmd.Init(_Inst, _World);																					  
	Cmd.Start();																								  
}																												  
																												  
void CheckHandler(Dispatcher& Dis, class UProject1GameInstance* Inst, UWorld* World)								  
{														
	Dis.AddHandler(EMessageType::SignInResult, std::bind(&OnMessageProcess<SignInResultMessageHandler, SignInResultMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::ServerDestroy, std::bind(&OnMessageProcess<ServerDestroyMessageHandler, ServerDestroyMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::SignUpResult, std::bind(&OnMessageProcess<SignUpResultMessageHandler, SignUpResultMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::Chat, std::bind(&OnMessageProcess<ChatMessageHandler, ChatMessage>, std::placeholders::_1, Inst, World));	
}																																													
