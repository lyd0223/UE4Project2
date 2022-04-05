// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalTrigger.h"


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

void APortalTrigger::TriggerBegin()
{
	//PrintViewport(1.f, FColor::Red, TEXT("Begin PortalTrigger"));
	
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
}

void APortalTrigger::TriggerEnd()
{
	//PrintViewport(1.f, FColor::Red, TEXT("End PortalTrigger"));
}

void APortalTrigger::SetTriggerSize(FVector SizeVector)
{
	UBoxComponent* Box = Cast<UBoxComponent>(m_Trigger);
	Box->SetBoxExtent(FVector(SizeVector));
}