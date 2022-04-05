// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingRoomPlayerController.h"

#include "Project1/WaitingRoomGameModeBase.h"
#include "Project1/NPC/NPC.h"
#include "Project1/NPC/Goat/Goat.h"
#include "Project1/NPC/Gremlin/Gremlin.h"
#include "Project1/Player/PlayerCharacter.h"
#include "Project1/UI/WaitingRoomLevel/WaitingRoomMainWidget.h"
#include "Project1/UI/WaitingRoomLevel/Store/StoreMainWidget.h"


AWaitingRoomPlayerController::AWaitingRoomPlayerController()
{
	m_TargetNPC = nullptr;
}

void AWaitingRoomPlayerController::BeginPlay()
{
	FInputModeGameAndUI Mode;
	SetInputMode(Mode);
	bShowMouseCursor = true;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetCharacter());
	if (PlayerCharacter)
		PlayerCharacter->SetIsWaitingRoom(true);
}

void AWaitingRoomPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//npc 마우스 커서 변경
	FHitResult result;
	GetHitResultUnderCursor(ECC_Visibility, true, result);
	if (result.bBlockingHit)
	{
		ANPC* NPC = Cast<ANPC>(result.GetActor());

		if (NPC)
		{
			//PrintViewport(0.1f, FColor::Blue, "NPC on the Cursor!");
			CurrentMouseCursor = EMouseCursor::Hand;

			if (m_TargetNPC != NPC)
			{
				m_TargetNPC = NPC;
			}
		}
		else
		{
			CurrentMouseCursor = EMouseCursor::Default;
		}
	}
}


void AWaitingRoomPlayerController::OpenWidget()
{
	//마우스커서가 npc 위에 올라가잇을때
	if (CurrentMouseCursor == EMouseCursor::Hand)
	{
		if (m_TargetNPC)
		{
			if (m_TargetNPC->GetIsActive())
			{
				AWaitingRoomGameModeBase* GameModeBase = Cast<AWaitingRoomGameModeBase>(GetWorld()->GetAuthGameMode());
				if(GameModeBase)
				{
					//상점
					if (m_TargetNPC->GetNPCName() == "Goat")
					{
						//PrintViewport(2.f, FColor::Blue, "Store Open");
						GameModeBase->GetMainWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						GameModeBase->GetMainWidget()->GetStoreMainWidget()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					}
					//유물
					else if (m_TargetNPC->GetNPCName() == "Gremlin")
					{
						//PrintViewport(2.f, FColor::Blue, "Relic Open");
					}
				}
			}
		}
	}
}