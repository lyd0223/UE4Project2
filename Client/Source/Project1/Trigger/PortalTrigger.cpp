// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalTrigger.h"

#include "Project1/Project1GameInstance.h"
#include "Project1/Player/PlayerCharacter.h"
#include "Project1/Player/WaitingRoomLevel/OtherPlayerCharacter.h"



APortalTrigger::APortalTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Trigger->SetCollisionProfileName("PlayerTrigger");
}

void APortalTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this, &APortalTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this, &APortalTrigger::TriggerEnd);
}

void APortalTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalTrigger::TriggerBegin(AActor* _OtherActor)
{
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetGameInstance());
	if(GameInstance == nullptr)
		return;
	//타 클라이언트 플레이어일때.
	if(Cast<APlayerCharacter>(_OtherActor) == nullptr)
	{
		_OtherActor->Destroy();
		
		AOtherPlayerCharacter* OtherPlayerCharacter = Cast<AOtherPlayerCharacter>(_OtherActor);
		GameInstance->RemovePlayingOtherCharacter(OtherPlayerCharacter->GetCharacterInfo().m_UserIdx);
		return;
	}
	GameInstance->RemoveAllPlayingOtherCharacter();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
}

void APortalTrigger::TriggerEnd(AActor* _OtherActor)
{
	
}

void APortalTrigger::SetTriggerSize(FVector SizeVector)
{
	UBoxComponent* Box = Cast<UBoxComponent>(m_Trigger);
	Box->SetBoxExtent(FVector(SizeVector));
}