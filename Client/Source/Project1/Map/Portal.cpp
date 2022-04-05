// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "../Trigger/PortalTrigger.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_PortalTrigger = nullptr;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	m_PortalTrigger = GetWorld()->SpawnActor<APortalTrigger>(APortalTrigger::StaticClass(), GetActorLocation(),
														GetActorRotation(), param);
	m_PortalTrigger->SetTriggerSize(FVector(100.f, 100.f, 100.f));

}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

