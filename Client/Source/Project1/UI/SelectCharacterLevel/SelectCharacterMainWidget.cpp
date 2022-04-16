// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterMainWidget.h"
#include "CharacterDescWidget.h"
#include "CharacterStatGraphWidget.h"
#include "../../Player/SelectCharacterPlayerController.h"
#include "Components/CanvasPanelSlot.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Global/ClientBlueprintFunctionLibrary.h"
#include "Project1/Global/Message/ClientToServer.h"
#include "CharacterNameSettingWidget.h"

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
	m_CharacterDescWidget->SetOwnerWidget(this);
	m_CharacterStatGraphWidget = Cast<UCharacterStatGraphWidget>(GetWidgetFromName(TEXT("UI_CharacterStatGraphWidget")));
	m_CharacterNameSettingWidget = Cast<UCharacterNameSettingWidget>(GetWidgetFromName(TEXT("UI_CharacterNameSettingWidget")));
	m_CharacterNameSettingWidget->SetOwnerWidget(this);
	
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

bool USelectCharacterMainWidget::UIInitialize(const std::vector<FCharacterInfo>& CharacterInfoList)
{
	m_CharacterInfoList = CharacterInfoList;
	for(auto& CharacterInfo :CharacterInfoList)
	{
		if(CharacterInfo.m_ClassName == "Belica")
		{
			m_CharacterInfoMap.Add(EPlayerJob::Belica, CharacterInfo);
			
		}
		else if(CharacterInfo.m_ClassName == "Revenant")
		{
			m_CharacterInfoMap.Add(EPlayerJob::Revenant, CharacterInfo);
			
		}
		else if(CharacterInfo.m_ClassName == "Wraith")
		{
			m_CharacterInfoMap.Add(EPlayerJob::Wraith, CharacterInfo);
			
		}
		else if(CharacterInfo.m_ClassName == "TwinBlaster")
		{
			m_CharacterInfoMap.Add(EPlayerJob::TwinBlaster, CharacterInfo);
			
		}
		else
		{
			PrintViewport(2.f, FColor::Red, TEXT("ClassName is worng!"));
			return false;
		}
	}

	//characterSelect 초기화면은 Belica 캐릭터로 되어있기때문에, 초기화면 설정.
	//스텟 이미지 변경
	m_CharacterStatGraphWidget->SetStatGraphImage(m_SelectJob);

	//캐릭터 설명 변경
	m_CharacterDescWidget->SetDesc(m_SelectJob,m_CharacterInfoMap);
	
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
		m_CharacterDescWidget->SetDesc(m_SelectJob,m_CharacterInfoMap);
		
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
		m_CharacterDescWidget->SetDesc(m_SelectJob,m_CharacterInfoMap);
		
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
		m_CharacterDescWidget->SetDesc(m_SelectJob,m_CharacterInfoMap);
		
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
		m_CharacterDescWidget->SetDesc(m_SelectJob,m_CharacterInfoMap);
		
		//컨트롤러 이동 (카메라 위치 이동)		
		ASelectCharacterPlayerController* PlayerController = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerController->Move(m_SelectJob);
	}
}

void USelectCharacterMainWidget::CreateButtonClick()
{
	if(m_IsCanEnter == true)
		return;
	m_CharacterNameSettingWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void USelectCharacterMainWidget::EnterButtonClick()
{
	if(m_IsCanEnter == false)
		return;
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	GameInstance->SetSelectJob(m_SelectJob);
	GameInstance->SetPlayingCharacterInfo(*m_CharacterInfoMap.Find(m_SelectJob));
	
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("WaitingRoom"));
}

void USelectCharacterMainWidget::BackButtonClick()
{
	//UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
	//	EQuitPreference::Quit, true);

	//------------------------------
	//모든 서버 설정 초기화해줘야하는부분..
	//추후 추가
	//------------------------------
	
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Start"));
	
}


void USelectCharacterMainWidget::EnterButtonOn(bool _IsOn)
{
	if(_IsOn)
	{
		m_IsCanEnter = true;
		m_CreateButton->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,0.3f));
		m_EnterButton->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,1.f));
	}
	else
	{
		m_IsCanEnter = false;
		m_CreateButton->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,1.f));
		m_EnterButton->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,0.3f));
		
	}
}