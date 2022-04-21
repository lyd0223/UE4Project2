// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameInstance.h"
#include "Manager/InventoryManager.h"

#include "Sockets.h"
#include "SocketSubSystem.h"
#include "Networking.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
//#include "GenericPlatform/GenericPlatformProcess.h"
#include "Global/Message/MessageConverter.h"


//ClientRecvThread -----------------------------------------------------------------------
ClientRecvThread::ClientRecvThread(FSocket* _RecvSocket, TQueue<std::shared_ptr<GameServerMessage>>* _MessageQueue) 
{
	if (nullptr == _RecvSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("RecvSocket Error"));
	}

	
	m_RecvSocket = _RecvSocket;
	m_IsAppClosed = false;
	m_MessageQueue = _MessageQueue;
}

uint32 ClientRecvThread::Run() 
{
	UE_LOG(LogTemp, Log, TEXT("Recv Start"));
	
	while (!m_IsAppClosed)
	{
	
		std::vector<uint8> RecvData;
		RecvData.resize(1024);
		int32 RecvDataSize_ = 0;
	
		//서버 접속체크
		if (false == m_RecvSocket->Recv(&RecvData[0], RecvData.size(), RecvDataSize_))
		{
			auto Result = m_RecvSocket->GetConnectionState();
	
			switch(Result)
			{
			case ESocketConnectionState::SCS_NotConnected:
				break;
			case ESocketConnectionState::SCS_Connected: 
				{
					// ServerDestroyMessage Message;
					// GameServerSerializer Serializer;
					// Message.Serialize(Serializer);
					//
					// MessageConverter Converter = MessageConverter(Serializer.GetData());
					// m_MessageQueue->Enqueue(Converter.GetServerMessage());
					// return 0;
				}
	
				break;
			case ESocketConnectionState::SCS_ConnectionError:
				break;
				
			}
			break;
		}
		
		MessageConverter Converter = MessageConverter(RecvData);
		m_MessageQueue->Enqueue(Converter.GetServerMessage());
	
	}
	 return 0;
}

void ClientRecvThread::Close()
{
	m_IsAppClosed = true;
}



//UProject1GameInstance ----------------------------------------------------------------------
UProject1GameInstance::UProject1GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>	MonsterInfoTableAsset(TEXT("DataTable'/Game/01Resources/Monster/DTMonsterInfo.DTMonsterInfo'"));
	if (MonsterInfoTableAsset.Succeeded())
		m_MonsterInfoTable = MonsterInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable>	PlayerInfoTableAsset(TEXT("DataTable'/Game/01Resources/Player/DTPlayerInfo.DTPlayerInfo'"));
	if (PlayerInfoTableAsset.Succeeded())
		m_PlayerInfoTable = PlayerInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>	SelectPlayerInfoTableAsset(TEXT("DataTable'/Game/01Resources/DataTable/DTSelectPlayerInfo.DTSelectPlayerInfo'"));
	if (SelectPlayerInfoTableAsset.Succeeded())
		m_SelectPlayerInfoTable = SelectPlayerInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>	ItemInfoTableAsset(TEXT("DataTable'/Game/01Resources/DataTable/DTItemTableInfo.DTItemTableInfo'"));
	if (ItemInfoTableAsset.Succeeded())
		m_ItemInfoTable = ItemInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>	BulletInfoTableAsset(TEXT("DataTable'/Game/01Resources/DataTable/DTBulletTableInfo.DTBulletTableInfo'"));
	if (BulletInfoTableAsset.Succeeded())
		m_BulletInfoTable = BulletInfoTableAsset.Object;

	m_SelectJob = EPlayerJob::Belica;
	
	m_InventoryManager = nullptr;

	m_IsServerConnected = false;
	m_IsClientMode = false;

	m_UserIdx = -1;
}

UProject1GameInstance::~UProject1GameInstance()
{
	if(m_RecvThread)
	{
		m_RecvThread->Exit();
		m_RecvThread = nullptr;
	}
}

void UProject1GameInstance::Init()
{
	Super::Init();
	m_InventoryManager = NewObject<UInventoryManager>(this, TEXT("InventoryManager"));
	m_InventoryManager->Init();
}

const FMonsterTableInfo* UProject1GameInstance::FindMonsterInfo(const FString& Name)
{
	return m_MonsterInfoTable->FindRow<FMonsterTableInfo>(*Name, "");
}

const FPlayerTableInfo* UProject1GameInstance::FindPlayerInfo(const FString& Name)
{
	return m_PlayerInfoTable->FindRow<FPlayerTableInfo>(*Name, "");
}

const FSelectPlayerTableInfo* UProject1GameInstance::FindSelectPlayerTableInfo(const FString& Name)
{
	return m_SelectPlayerInfoTable->FindRow<FSelectPlayerTableInfo>(*Name, "");
}

const FItemTableInfo* UProject1GameInstance::FindItemTableInfo(const FString& Name)
{
	return m_ItemInfoTable->FindRow<FItemTableInfo>(*Name, "");
}

const FItemTableInfo* UProject1GameInstance::FindItemTableInfo(int Index)
{
	TArray<FName> NameArray = m_ItemInfoTable->GetRowNames();
	return m_ItemInfoTable->FindRow<FItemTableInfo>(NameArray[Index], "");
}

const FBulletTableInfo* UProject1GameInstance::FindBulletTableInfo(const FString& Name)
{
	return m_BulletInfoTable->FindRow<FBulletTableInfo>(*Name, "");
}


//-----------------------------------서버코드------------------------------------

bool UProject1GameInstance::ServerConnect(const FString& _IPString, const FString& _PORTString)
{
	if (ThreadAvailableCheck() == false)
	{
		return false;
	}

	Close();

	m_SocketSubSystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	// 이 Level Login Level에서 만들어졌다고 치고

	m_Socket = m_SocketSubSystem->CreateSocket(NAME_Stream, "Test", false);

	if (nullptr == m_Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == NewSocket)"));
		return false;
	}

	m_Socket ->SetNoDelay(true);

	FIPv4Address ConnectAddress;
	FIPv4Address::Parse(_IPString, ConnectAddress);
	int Port = static_cast<uint16>(FCString::Atoi(*_PORTString));
	FIPv4Endpoint EndPoint = FIPv4Endpoint(ConnectAddress, Port);
	
	if (false == m_Socket->Connect(EndPoint.ToInternetAddr().Get()))
	{
		m_SocketSubSystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
		FString ErrorText = m_SocketSubSystem->GetSocketError(m_SocketSubSystem->GetLastErrorCode());
		
		UE_LOG(LogTemp, Error, TEXT("Server Error : %s"), *ErrorText);
		m_Socket->Close();
		m_Socket = nullptr;
		return false;
	}

	//TCP소켓 노딜레이옵션.
	m_Socket->SetNoDelay(true);
	
	m_RecvThread = new ClientRecvThread(m_Socket, &m_MessageQueue);
	m_ThreadRunalbe = FRunnableThread::Create(m_RecvThread, TEXT("Recv Thread"));
	
	return true;
}

bool UProject1GameInstance::Send(const std::vector<uint8>& _Data)
{
	if(m_Socket == nullptr)
	{
		return false;
	}
	if (0 == _Data.size())
	{
		return false;
	}

	int32 DataSendSize = 0;

	return m_Socket->Send(&_Data[0], _Data.size(), DataSendSize);
}

//클라이언트모드 전용푸시함수.
void UProject1GameInstance::PushClientMessage(std::shared_ptr<GameServerMessage> _Message)
{
	if(m_IsClientMode)
		return;

	m_MessageQueue.Enqueue(_Message);
}

std::shared_ptr<GameServerMessage> UProject1GameInstance::PopMessage()
{
	std::shared_ptr<GameServerMessage> Message;
	m_MessageQueue.Dequeue(Message);

	return Message;
}


void UProject1GameInstance::FinishDestroy()
{
	Close();

	Super::FinishDestroy();
}

//플랫폼에서 멀티프로세스를 지원하는지 체크하는 함수.
bool UProject1GameInstance::ThreadAvailableCheck() 
{
	if (false == FPlatformProcess::SupportsMultithreading())
	{
		UE_LOG(LogTemp, Error, TEXT("Is Not Support Multithreading"));
		return false;
	}

	return true;
}

void UProject1GameInstance::Close() 
{
	if(m_RecvThread)
	{
		m_RecvThread->Close();
	}
	
	if (m_Socket == nullptr)
	{
		return;
	}

	m_Socket->Close();
	m_Socket = nullptr;
}

void UProject1GameInstance::SetPlayingCharacterInfo(const FPlayerInfo& PlayerInfo)
{
	m_PlayingCharacterInfo.m_LV = PlayerInfo.Level;
	m_PlayingCharacterInfo.m_EXP = PlayerInfo.EXP;
	m_PlayingCharacterInfo.m_ATK = PlayerInfo.ATK;
	m_PlayingCharacterInfo.m_DEF = PlayerInfo.DEF;
	m_PlayingCharacterInfo.m_HP = PlayerInfo.HPMax;
	m_PlayingCharacterInfo.m_SP = PlayerInfo.SPMax;
	m_PlayingCharacterInfo.m_AttackSpeed = PlayerInfo.AttackSpeed;
	m_PlayingCharacterInfo.m_MoveSpeed = PlayerInfo.MoveSpeed;
	//InventoryData
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	if(GameInstance == nullptr)
		return;
	UInventoryManager* InventoryManager = GameInstance->GetInventoryManager();
	if(InventoryManager == nullptr)
		return;
	InventoryManager->SaveCharacterInfoInventoryData(m_PlayingCharacterInfo);
}