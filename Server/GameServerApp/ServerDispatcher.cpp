#include "PreCompile.h"																																							
#include "ServerDispatcher.h"																																						
#include <GameServerBase\GameServerDebug.h>																																			
																																													
#include "SignInMessageHandler.h"
#include "SignUpMessageHandler.h"
#include "CreateCharacterInfoMessageHandler.h"
#include "DeleteCharacterInfoMessageHandler.h"
#include "RequestCharacterInfoMessageHandler.h"
#include "SaveCharacterInfoMessageHandler.h"
#include "ChatMessageHandler.h"
#include "CharacterMoveMessageHandler.h"
																																													
Dispatcher<TCPSession> gDispatcher;																																							
																																													
template<typename MessageHandler, typename EMessageType>																																
void OnMessageProcess(std::shared_ptr<TCPSession> _Session, std::shared_ptr<GameServerMessage> _Message)																			
{																																													
	std::shared_ptr<EMessageType> ConvertMessage = std::dynamic_pointer_cast<EMessageType>(_Message);																					
	if (nullptr == ConvertMessage)																																					
	{																																												
		GameServerDebug::LogError("ConvertError");																																
		return;																																										
	}																																												
																																													
	std::shared_ptr<MessageHandler> Cmd = std::make_shared<MessageHandler>();																				
	Cmd->Init(_Session, ConvertMessage);																																			
	Cmd->Start();																																									
}																																													
																																													
void DispatcherRegistration()																																						
{																																													
	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::SignIn), std::bind(&OnMessageProcess<SignInMessageHandler, SignInMessage>, std::placeholders::_1, std::placeholders::_2));	
	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::SignUp), std::bind(&OnMessageProcess<SignUpMessageHandler, SignUpMessage>, std::placeholders::_1, std::placeholders::_2));	
	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::CreateCharacterInfo), std::bind(&OnMessageProcess<CreateCharacterInfoMessageHandler, CreateCharacterInfoMessage>, std::placeholders::_1, std::placeholders::_2));	
	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::DeleteCharacterInfo), std::bind(&OnMessageProcess<DeleteCharacterInfoMessageHandler, DeleteCharacterInfoMessage>, std::placeholders::_1, std::placeholders::_2));	
	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::RequestCharacterInfo), std::bind(&OnMessageProcess<RequestCharacterInfoMessageHandler, RequestCharacterInfoMessage>, std::placeholders::_1, std::placeholders::_2));	
	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::SaveCharacterInfo), std::bind(&OnMessageProcess<SaveCharacterInfoMessageHandler, SaveCharacterInfoMessage>, std::placeholders::_1, std::placeholders::_2));	
	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::Chat), std::bind(&OnMessageProcess<ChatMessageHandler, ChatMessage>, std::placeholders::_1, std::placeholders::_2));	
	gDispatcher.AddHandler(static_cast<uint32_t>(EMessageType::CharacterMove), std::bind(&OnMessageProcess<CharacterMoveMessageHandler, CharacterMoveMessage>, std::placeholders::_1, std::placeholders::_2));	
}																																													
