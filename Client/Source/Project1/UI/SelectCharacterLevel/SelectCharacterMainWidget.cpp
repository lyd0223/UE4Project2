// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterMainWidget.h"
#include "CharacterDescWidget.h"
#include "CharacterStatGraphWidget.h"
#include "../../Player/SelectCharacterPlayerController.h"
#include "Components/CanvasPanelSlot.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Global/ClientBlueprintFunctionLibrary.h"
#include "Project1/Global/Message/ClientToServer.h"

void USelectCharacterMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_Character1Button = Cast<UButton>(GetWidgetFromName(TEXT("Character1Button")));
	m_Character2Button = Cast<UButton>(GetWidgetFromName(TEXT("Character2Button")));
	m_Character3Button = Cast<UButton>(GetWidgetFromName(TEXT("Character3Button")));
	m_Character4Button = Cast<UButton>(GetWidgetFromName(TEXT("Character4Button")));
	m_CreateButton = Cast<UButton>(GetWidgetFromName(TEXT("CreateButton")));
	m_EnterButton = Cast<UButton>(GetWidgetFromName(TEXT("EnterButton")));
	m_BackButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));
	m_CharacterDescWidget = Cast<UCharacterDescWidget>(GetWidgetFromName(TEXT("UI_CharacterDescWidget")));
	m_CharacterStatGraphWidget = Cast<UCharacterStatGraphWidget>(GetWidgetFromName(TEXT("UI_CharacterStatGraphWidget")));

	m_Character1Button->OnClicked.AddDynamic(this, &USelectCharacterMainWidget::Character1ButtonClick);
	m_Character2Button->OnClicked.AddDynamic(this, &USelectCharacterMainWidget::Character2ButtonClick);
	m_Character3Button->OnClicked.AddDynamic(this, &USelectCharacterMainWidget::Character3ButtonClick);
	m_Character4Button->OnClicked.AddDynamic(this, &USelectCharacterMainWidget::Character4ButtonClick);
	m_CreateButton->OnClicked.AddDynamic(this, &USelectCharacterMainWidget::CreateButtonClick);
	m_BackButton->OnClicked.AddDynamic(this, &USelectCharacterMainWidget::BackButtonClick);
	m_EnterButton->OnClicked.AddDynamic(this, &USelectCharacterMainWidget::EnterButtonClick);

	m_SelectJob = EPlayerJob::Belica;
	
	m_SelectPanelSlot = Cast<UCanvasPanelSlot>(m_Character1Button->GetParent()->Slot);
	FVector2D Pos = m_SelectPanelSlot->GetPosition();
	Pos.X += 50.f;
	m_SelectPanelSlot->SetPosition(Pos);

	
}

void USelectCharacterMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

bool USelectCharacterMainWidget::UIInitialize(std::vector<FCharacterInfo>& CharacterInfoList)
{
	m_CharacterInfoList = CharacterInfoList;
	for(auto& CharacterInfo :CharacterInfoList)
	{
		FString String = TEXT("");
		String += FString::Printf(TEXT("캐릭터이름 : %s\n"), CharacterInfo.m_Nickname.c_str());
		String += FString::Printf(TEXT("LV\t : %d\n"), CharacterInfo.m_LV);
		String += FString::Printf(TEXT("HP\t : %f\n"), CharacterInfo.m_HP);
		String += FString::Printf(TEXT("MP\t : %f\n"), CharacterInfo.m_MP);
		String += FString::Printf(TEXT("ATK\t : %f\n"), CharacterInfo.m_ATK);
		
		if(CharacterInfo.m_ClassName == "Belica")
		{
			m_CharacterDescMap.Add(EPlayerJob::Belica, String);
			
		}
		else if(CharacterInfo.m_ClassName == "Revenant")
		{
			m_CharacterDescMap.Add(EPlayerJob::Revenant, String);
			
		}
		else if(CharacterInfo.m_ClassName == "Wraith")
		{
			m_CharacterDescMap.Add(EPlayerJob::Wraith, String);
			
		}
		else if(CharacterInfo.m_ClassName == "TwinBlaster")
		{
			m_CharacterDescMap.Add(EPlayerJob::TwinBlaster, String);
			
		}
		else
		{
			PrintViewport(2.f, FColor::Red, TEXT("ClassName is worng!"));
			return false;
		}
		
		
	}
	
	return true;
}

void USelectCharacterMainWidget::Character1ButtonClick()
{
	if(m_SelectJob != EPlayerJob::Belica)
	{
		m_SelectJob = EPlayerJob::Belica;
		
		//버튼 위치변경
		if(m_SelectPanelSlot)
		{
			FVector2D SlotPosition = m_SelectPanelSlot->GetPosition();
			SlotPosition.X -= 50.f;
			m_SelectPanelSlot->SetPosition(SlotPosition);
		}
		m_SelectPanelSlot = Cast<UCanvasPanelSlot>(m_Character1Button->GetParent()->Slot);
		FVector2D SlotPosition = m_SelectPanelSlot->GetPosition();
		SlotPosition.X += 50.f;
		m_SelectPanelSlot->SetPosition(SlotPosition);

		//스텟 이미지 변경
		m_CharacterStatGraphWidget->SetStatGraphImage(m_SelectJob);

		//캐릭터 설명 변경
		if(m_CharacterDescMap.Find(EPlayerJob::Belica))
		{
			m_CharacterDescWidget->SetDesc(m_CharacterDescMap[EPlayerJob::Belica]);
			//m_CreateButton->
		}
		else
		{
			m_CharacterDescWidget->SetDesc(m_SelectJob);
		}
		
		//컨트롤러 이동 (카메라 위치 이동)
		ASelectCharacterPlayerController* PlayerController = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerController->Move(m_SelectJob);
	}

}
void USelectCharacterMainWidget::Character2ButtonClick()
{
	if(m_SelectJob != EPlayerJob::Revenant)
	{
		m_SelectJob = EPlayerJob::Revenant;
		
		//버튼 위치변경
		if(m_SelectPanelSlot)
		{
			FVector2D SlotPosition = m_SelectPanelSlot->GetPosition();
			SlotPosition.X -= 50.f;
			m_SelectPanelSlot->SetPosition(SlotPosition);
		}
		m_SelectPanelSlot = Cast<UCanvasPanelSlot>(m_Character2Button->GetParent()->Slot);
		FVector2D SlotPosition = m_SelectPanelSlot->GetPosition();
		SlotPosition.X += 50.f;
		m_SelectPanelSlot->SetPosition(SlotPosition);

		//스텟 이미지 변경
		m_CharacterStatGraphWidget->SetStatGraphImage(m_SelectJob);

		//캐릭터 설명 변경
		m_CharacterDescWidget->SetDesc(m_SelectJob);
		
		//컨트롤러 이동 (카메라 위치 이동)
		ASelectCharacterPlayerController* PlayerController = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerController->Move(m_SelectJob);
	}
}

void USelectCharacterMainWidget::Character3ButtonClick()
{
	if(m_SelectJob != EPlayerJob::Wraith)
	{
		m_SelectJob = EPlayerJob::Wraith;
		
		//버튼 위치변경
		if(m_SelectPanelSlot)
		{
			FVector2D SlotPosition = m_SelectPanelSlot->GetPosition();
			SlotPosition.X -= 50.f;
			m_SelectPanelSlot->SetPosition(SlotPosition);
		}
		m_SelectPanelSlot = Cast<UCanvasPanelSlot>(m_Character3Button->GetParent()->Slot);
		FVector2D SlotPosition = m_SelectPanelSlot->GetPosition();
		SlotPosition.X += 50.f;
		m_SelectPanelSlot->SetPosition(SlotPosition);

		//스텟 이미지 변경
		m_CharacterStatGraphWidget->SetStatGraphImage(m_SelectJob);

		//캐릭터 설명 변경
		m_CharacterDescWidget->SetDesc(m_SelectJob);
		
		//컨트롤러 이동 (카메라 위치 이동)
		ASelectCharacterPlayerController* PlayerController = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerController->Move(m_SelectJob);
	}
}
void USelectCharacterMainWidget::Character4ButtonClick()
{
	if(m_SelectJob != EPlayerJob::TwinBlaster)
	{
		m_SelectJob = EPlayerJob::TwinBlaster;
		
		//버튼 위치변경
		if(m_SelectPanelSlot)
		{
			FVector2D SlotPosition = m_SelectPanelSlot->GetPosition();
			SlotPosition.X -= 50.f;
			m_SelectPanelSlot->SetPosition(SlotPosition);
		}
		m_SelectPanelSlot = Cast<UCanvasPanelSlot>(m_Character4Button->GetParent()->Slot);
		FVector2D SlotPosition = m_SelectPanelSlot->GetPosition();
		SlotPosition.X += 50.f;
		m_SelectPanelSlot->SetPosition(SlotPosition);

		//스텟 이미지 변경
		m_CharacterStatGraphWidget->SetStatGraphImage(m_SelectJob);

		//캐릭터 설명 변경
		m_CharacterDescWidget->SetDesc(m_SelectJob);

		//컨트롤러 이동 (카메라 위치 이동)		
		ASelectCharacterPlayerController* PlayerController = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerController->Move(m_SelectJob);
	}
}

void USelectCharacterMainWidget::CreateButtonClick()
{
	//서버로 캐릭터인포 생성 패킷 보내기.--------------------------------------------------------
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());
	if(GameInst->GetIsClientMode())
		return;		
	CreateCharacterInfoMessage Message;

	//캐릭터 정보 불러오기
	FString ClassName = TEXT("");
	switch(m_SelectJob)
	{
		case EPlayerJob::Belica :
			ClassName = TEXT("Belica");
			break;
		case EPlayerJob::Revenant :
			ClassName = TEXT("Revenant");
			break;
		case EPlayerJob::Wraith :
			ClassName = TEXT("Wraith");
			break;
		case EPlayerJob::TwinBlaster :
			ClassName = TEXT("TwinBlaster");
			break;
	}
	
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	const FPlayerTableInfo* Info = GameInstance->FindPlayerInfo(ClassName);

	FCharacterInfo& CharacterInfo = Message.m_CharacterInfo;
	if (Info)
	{
		UClientBlueprintFunctionLibrary::FStringToUTF8(Info->Name, CharacterInfo.m_Nickname);
		UClientBlueprintFunctionLibrary::FStringToUTF8(ClassName, CharacterInfo.m_ClassName);
		CharacterInfo.m_LV = Info->Level;
		CharacterInfo.m_HP = Info->HPMax;
		// m_PlayerInfo.SPMax = Info->SPMax;
		// m_PlayerInfo.EXP = Info->EXP;
		// m_PlayerInfo.ATK = Info->ATK;
		// m_PlayerInfo.DEF = Info->DEF;
		// m_PlayerInfo.AttackSpeed = Info->AttackSpeed;
		//m_PlayerInfo.MoveSpeed = Info->MoveSpeed;
	}
	
	GameServerSerializer Serializer;
	Message.Serialize(Serializer);
	
	if (!GameInst->Send(Serializer.GetData()))
	{
		PrintViewport(2.f, FColor::Red, TEXT("SignUp Message Send Error!"));
	}
	//--------------------------------------------------------------------------------------
}

void USelectCharacterMainWidget::EnterButtonClick()
{
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	GameInstance->SetSelectJob(m_SelectJob);
	//SetSelectCharacter(); 로변경
	
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("WaitingRoom"));
}

void USelectCharacterMainWidget::BackButtonClick()
{
	//UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
	//	EQuitPreference::Quit, true);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Start"));
}
