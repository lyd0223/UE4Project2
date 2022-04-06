#include "PreCompile.h"
#include <iostream>
#include <process.h>
#include <Windows.h>
#include <thread>
#include <conio.h>

#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerIocp.h>
#include <GameServerBase/GameServerQueue.h>
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerSerializer.h>
#include <GameServerBase/GameServerString.h>

#include <GameServerNet/TCPListener.h>
#include <GameServerNet/TCPSession.h>
#include <GameServerNet/ServerHelper.h>

#include <GameServerMessage/GameServerMessage.h>
#include <GameServerMessage/Dispatcher.h>
#include <GameServerMessage/MessageConverter.h>

#include "NetQueue.h"
#include "DBQueue.h"
#include "ServerDispatcher.h"


#define _CRTDBG_MAP_ALLOC

int main() 
{
	//_CrtSetBreakAlloc(156);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtDumpMemoryLeaks();
	NetQueue::Initialize();
	DBQueue::Initialize();

	DispatcherRegistration();

	ServerHelper::StartEngineStartUp();
	GameServerDebug::Initialize();

	PtrSTCPListener NewListener = std::make_shared<TCPListener>();

	NewListener->Initialize(IPEndPoint(IPAddress::Parse("0.0.0.0"), 30001), [](PtrSTCPSession _S)
		{
			
			_S->SetCallBack(
				//Packet받았을떄 CallBack
				[&](PtrSTCPSession _S, const std::vector<unsigned char>& _Value)
				{
					MessageConverter Converter = MessageConverter(_Value);
				
					MessageHandler<TCPSession> Handler;
					bool check = gDispatcher.GetHandler(Converter.GetMessageTypeByuint(), Handler);
					if (!check)
					{
						GameServerDebug::LogError("GetHandler Error");
						return;
					}
					Handler(_S, Converter.GetServerMessage());
				},
				//Socket연결끊겼을때 CallBack
				[](PtrSTCPSession _S)
				{
					std::string LogText = std::to_string(static_cast<int>(_S->GetSocket()));
					GameServerDebug::LogInfo(LogText + "Unconnected.");
				});


			std::string LogText = std::to_string(static_cast<int>(_S->GetSocket()));

			GameServerDebug::LogInfo(LogText + "Connected.");
		}
	);

	NewListener->BindQueue(NetQueue::GetQueue());
	NewListener->StartAccept(10);
	
	GameServerDebug::LogInfo("Server Start.");

	
	while (1)
	{
		if (_getch() == 'q')
			break;
	}

	NetQueue::Destroy();
	DBQueue::Destroy();

	GameServerDebug::Destroy();
}