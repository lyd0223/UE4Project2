// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBoxTrigger.h"

#include "Project1/Project1GameModeBase.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Map/LootBox.h"
#include "Project1/Player/PlayerCharacter.h"
#include "Project1/UI/MainHUDWidget.h"
#include "Project1/UI/Loot/LootListItemData.h"


ALootBoxTrigger::ALootBoxTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Trigger->SetCollisionProfileName("PlayerTrigger");

	m_IsTriggerOn = false;
}

void ALootBoxTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this, &ALootBoxTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this, &ALootBoxTrigger::TriggerEnd);
}

void ALootBoxTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_IsTriggerOn)
	{
		AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if(IsValid(GameModeBase))
		{
			bool IsKeyDown = GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::F);
			if(IsKeyDown)
			{
				m_OwnerLootBox->GetMesh()->Play(false);
				ESlateVisibility Visibility = GameModeBase->GetMainHUDWidget()->GetLootHUD()->GetVisibility();
				if(Visibility == ESlateVisibility::Collapsed)
				{
					ULootHUDWidget* LootHudWidget = GameModeBase->GetMainHUDWidget()->GetLootHUD();
					LootHudWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					LootHudWidget->SetLootBox(m_OwnerLootBox);

					LootHudWidget->GetLootListView()->ClearListItems();
					
					for(auto Item : m_OwnerLootBox->GetDropItemArray())
					{
						ULootListItemData* ItemData = NewObject<ULootListItemData>(this, ULootListItemData::StaticClass());
						ItemData->SetItem(Item);
						LootHudWidget->GetLootListView()->AddItem(ItemData);
					}
					
					APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
					FInputModeGameAndUI Mode;
					PlayerController->SetInputMode(Mode);
					PlayerController->bShowMouseCursor = true;
					
					APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
					PlayerCharacter->SetIsUIMode(true);
				}
				else
				{
					GameModeBase->GetMainHUDWidget()->GetLootHUD()->SetVisibility(ESlateVisibility::Collapsed);

					APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
					FInputModeGameOnly Mode;
					PlayerController->SetInputMode(Mode);
					PlayerController->bShowMouseCursor = false;
					
					APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
					PlayerCharacter->SetIsUIMode(false);
				}

				FActorSpawnParameters param;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), GetActorLocation(),
					FRotator::ZeroRotator, param);
				Effect->LoadSoundAsync(TEXT("OpenWidget"));
				Effect->SetLifeTime(1.f);
			}
		}
	}
}

void ALootBoxTrigger::TriggerBegin()
{
	//PrintViewport(1.f, FColor::Red, TEXT("Begin LootBoxTrigger"));
	
	m_IsTriggerOn = true;
	
	//UI On
	if(m_OwnerLootBox)
		m_OwnerLootBox->GetWidgetComponent()->SetVisibility(true);
}

void ALootBoxTrigger::TriggerEnd()
{
	//PrintViewport(1.f, FColor::Red, TEXT("End LootBoxTrigger"));

	m_IsTriggerOn = false;
	
	//UI Off
	m_OwnerLootBox->GetWidgetComponent()->SetVisibility(false);
	
	AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameModeBase))
		GameModeBase->GetMainHUDWidget()->GetLootHUD()->SetVisibility(ESlateVisibility::Collapsed);
}

void ALootBoxTrigger::SetTriggerSize(FVector SizeVector)
{
	UBoxComponent* Box = Cast<UBoxComponent>(m_Trigger);
	Box->SetBoxExtent(FVector(SizeVector));
}