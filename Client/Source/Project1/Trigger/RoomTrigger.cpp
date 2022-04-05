// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTrigger.h"
#include "../Map/Room.h"

ARoomTrigger::ARoomTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Trigger->SetCollisionProfileName("PlayerTrigger");
}

void ARoomTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this, &ARoomTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this, &ARoomTrigger::TriggerEnd);
}

void ARoomTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomTrigger::TriggerBegin()
{
	//PrintViewport(1.f, FColor::Red, TEXT("Begin Trigger"));

	if(m_OwnerRoom)
	{
		m_OwnerRoom->Enter();
	}
	
}

void ARoomTrigger::TriggerEnd()
{
	//PrintViewport(1.f, FColor::Red, TEXT("End Trigger"));
}

void ARoomTrigger::SetTriggerSize(FVector SizeVector)
{
	UBoxComponent* Box = Cast<UBoxComponent>(m_Trigger);
	Box->SetBoxExtent(FVector(SizeVector));
}
FVector2D ARoomTrigger::GetTriggerSize()
{
	UBoxComponent* Box = Cast<UBoxComponent>(m_Trigger);
	FVector Size3D = Box->GetScaledBoxExtent();
	FVector2D Size2D;
	Size2D.X = Size3D.X;
	Size2D.Y = Size3D.Y;

	return Size2D;
}