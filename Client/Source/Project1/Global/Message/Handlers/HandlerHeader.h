#pragma once																									  
#include "CoreMinimal.h"																						  
#include <functional>																								
#include "../Dispatcher.h"																						
																												  
#include "SignInResultMessageHandler.h"
#include "ServerDestroyMessageHandler.h"
#include "SignUpResultMessageHandler.h"
#include "CreateCharacterInfoResultMessageHandler.h"
#include "ReplyCharacterInfoMessageHandler.h"
#include "ChatMessageHandler.h"
#include "CharacterMoveMessageHandler.h"
																												  
template<class MessageHandler, class MessageType>															  
void OnMessageProcess(std::shared_ptr<GameServerMessage> _Message, class UProject1GameInstance* _Inst, UWorld* _World)	  
{																												  
	std::shared_ptr<MessageType> ConvertMessage = std::static_pointer_cast<MessageType>(_Message);				  
	if (nullptr == ConvertMessage)																				  
	{																											  
		return;																									  
	}																											  
																												  
	MessageHandler Cmd = MessageHandler();														  
	Cmd.Init(_Inst, _World, ConvertMessage);																					  
	Cmd.Start();																								  
}																												  
																												  
void CheckHandler(Dispatcher& Dis, class UProject1GameInstance* Inst, UWorld* World)								  
{														
	Dis.AddHandler(EMessageType::SignInResult, std::bind(&OnMessageProcess<SignInResultMessageHandler, SignInResultMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::ServerDestroy, std::bind(&OnMessageProcess<ServerDestroyMessageHandler, ServerDestroyMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::SignUpResult, std::bind(&OnMessageProcess<SignUpResultMessageHandler, SignUpResultMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::CreateCharacterInfoResult, std::bind(&OnMessageProcess<CreateCharacterInfoResultMessageHandler, CreateCharacterInfoResultMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::ReplyCharacterInfo, std::bind(&OnMessageProcess<ReplyCharacterInfoMessageHandler, ReplyCharacterInfoMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::Chat, std::bind(&OnMessageProcess<ChatMessageHandler, ChatMessage>, std::placeholders::_1, Inst, World));	
	Dis.AddHandler(EMessageType::CharacterMove, std::bind(&OnMessageProcess<CharacterMoveMessageHandler, CharacterMoveMessage>, std::placeholders::_1, Inst, World));	
}																																													
