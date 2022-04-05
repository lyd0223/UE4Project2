// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCTrigger.h"

#include "Project1/NPC/NPC.h"


ANPCTrigger::ANPCTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Trigger->SetCollisionProfileName("PlayerTrigger");
}

void ANPCTrigger::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerBeginDelegate.AddDynamic(this, &ANPCTrigger::TriggerBegin);
	m_TriggerEndDelegate.AddDynamic(this, &ANPCTrigger::TriggerEnd);
}

void ANPCTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPCTrigger::TriggerBegin()
{
	//PrintViewport(1.f, FColor::Red, TEXT("Begin NPCTrigger"));
	
	if(m_OwnerNPC)
	{
		m_OwnerNPC->GetBillboard()->SetHiddenInGame(false);
		m_OwnerNPC->SetIsActive(true);
	}
}

void ANPCTrigger::TriggerEnd()
{
	//PrintViewport(1.f, FColor::Red, TEXT("End NPCTrigger"));
	if(m_OwnerNPC)
	{
		m_OwnerNPC->GetBillboard()->SetHiddenInGame(true);
		m_OwnerNPC->SetIsActive(false);
	}
}

void ANPCTrigger::SetTriggerSize(float Radious)
{
	USphereComponent* Sphere = Cast<USphereComponent>(m_Trigger);
	Sphere->SetSphereRadius(Radious);
}