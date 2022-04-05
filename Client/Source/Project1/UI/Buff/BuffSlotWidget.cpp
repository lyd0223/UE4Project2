// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffSlotWidget.h"

#include "BuffMainWidget.h"
#include "Project1/Player/PlayerCharacter.h"


void UBuffSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_BuffImage = Cast<UImage>(GetWidgetFromName(TEXT("BuffImage")));
	m_CooldownImage = Cast<UImage>(GetWidgetFromName(TEXT("CooldownImage")));

	//ItemImage 이미지 초기화.
	m_BuffImage->SetBrushFromTexture(nullptr);

	//쿨타임 머테리얼 다이나믹설정.
	UMaterialInstance* MTInst = Cast<UMaterialInstance>(m_CooldownImage->Brush.GetResourceObject());
	m_MTInstDynamic = UMaterialInstanceDynamic::Create(MTInst, this);
	m_CooldownImage->SetBrushFromMaterial(m_MTInstDynamic);

	SetVisibility(ESlateVisibility::Collapsed);
	m_Time = 0.f;
	m_AccTime = 0.f;

	m_IsActive = false;
}

void UBuffSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (m_IsActive)
	{
		m_AccTime += InDeltaTime;

		float Percent = m_AccTime / m_Time;
		m_MTInstDynamic->SetScalarParameterValue("percent", Percent);

		//쿨타임 다됐을때
		if (m_AccTime >= m_Time)
		{
			BuffEnd();
		}
	}
}

void UBuffSlotWidget::BuffEnd()
{
	m_BuffImage->SetBrushFromTexture(nullptr);
	m_Time = 0.f;
	m_AccTime = 0.f;
	m_IsActive = false;

	SetVisibility(ESlateVisibility::Collapsed);

	m_OwnerBuffMainWidget->BuffRefresh(m_Index);

	//PlayerInfo 변경.
	APlayerCharacter* PlayerCharacter = m_OwnerBuffMainWidget->GetPlayerCharacter();
	for (auto ItemOption : m_ItemTableInfo->ItemOptionArray)
	{
		FPlayerInfo& PlayerInfo = PlayerCharacter->GetPlayerInfo();
		switch (ItemOption.OptionType)
		{
		default:
			break;
		case EItemOptionType::Attack:
			PlayerInfo.ATK -= ItemOption.OptionAmount;
			break;
		case EItemOptionType::AttackSpeed:
			PlayerInfo.AttackSpeed -= ItemOption.OptionAmount;
			break;
		}
	}
	PlayerCharacter->SetUI();
	m_ItemTableInfo = nullptr;
}

void UBuffSlotWidget::BuffStart(const FItemTableInfo* ItemTableInfo, float Duration)
{
	m_ItemTableInfo = ItemTableInfo;

	m_BuffImage->SetBrushFromTexture(ItemTableInfo->IconTexture);
	m_Time = Duration;
	m_IsActive = true;

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	//PlayerInfo 변경.
	APlayerCharacter* PlayerCharacter = m_OwnerBuffMainWidget->GetPlayerCharacter();
	if (PlayerCharacter)
	{
		for (auto ItemOption : m_ItemTableInfo->ItemOptionArray)
		{
			FPlayerInfo& PlayerInfo = PlayerCharacter->GetPlayerInfo();
			switch (ItemOption.OptionType)
			{
			default:
				break;
			case EItemOptionType::Attack:
				PlayerInfo.ATK += ItemOption.OptionAmount;
				break;
			case EItemOptionType::AttackSpeed:
				PlayerInfo.AttackSpeed += ItemOption.OptionAmount;
				break;
			}
		}
		PlayerCharacter->SetUI();
	}
}

void UBuffSlotWidget::BuffSlotChange(UBuffSlotWidget* NextBuffSlotWidget)
{
	m_Time = NextBuffSlotWidget->GetTime();
	m_AccTime = NextBuffSlotWidget->GetAccTime();
	m_IsActive = NextBuffSlotWidget->GetIsActive();
	UTexture2D* Texture = Cast<UTexture2D>(NextBuffSlotWidget->m_BuffImage->Brush.GetResourceObject());
	m_BuffImage->SetBrushFromTexture(Texture);

	SetVisibility(ESlateVisibility::HitTestInvisible);

	NextBuffSlotWidget->BuffSlotReset();
}


void UBuffSlotWidget::BuffSlotReset()
{
	m_Time = 0.f;
	m_AccTime = 0.f;
	m_IsActive = false;
	m_BuffImage->SetBrushFromTexture(nullptr);

	this->SetVisibility(ESlateVisibility::Collapsed);
}
