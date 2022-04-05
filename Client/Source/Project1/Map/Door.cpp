// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Project1/Effect/NormalEffect.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_RightDoor = nullptr;
	m_LeftDoor = nullptr;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	m_LeftDoor = Cast<UStaticMeshComponent>(RootComponent->GetChildComponent(0)->GetChildComponent(0));
	m_RightDoor = Cast<UStaticMeshComponent>(RootComponent->GetChildComponent(0)->GetChildComponent(1));
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::Open()
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), GetActorLocation(),
		FRotator::ZeroRotator, param);
	Effect->LoadSoundAsync(TEXT("Door"));
	Effect->SetLifeTime(1.f);
	
	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &ADoor::DoorOpen, 0.03f, true);
}

void ADoor::Close()
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), GetActorLocation(),
		FRotator::ZeroRotator, param);
	Effect->LoadSoundAsync(TEXT("Door"));
	Effect->SetLifeTime(1.f);
	
	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &ADoor::DoorClose, 0.03f, true);
}

void ADoor::DoorOpen()
{
	FRotator LeftDoorRot = m_LeftDoor->GetRelativeRotation();
	if(LeftDoorRot.Yaw <= 90.f)
		m_LeftDoor->AddRelativeRotation(FRotator(0.f,1.f,0.f));
	FRotator RightDoorRot = m_RightDoor->GetRelativeRotation();
	if(RightDoorRot.Yaw >= -90.f)
		m_RightDoor->AddRelativeRotation(FRotator(0.f,-1.f,0.f));
	
	if(LeftDoorRot.Yaw >= 90.f && RightDoorRot.Yaw <= -90.f)
		GetWorldTimerManager().ClearTimer(m_TimerHandle);
}
void ADoor::DoorClose()
{
	FRotator LeftDoorRot = m_LeftDoor->GetRelativeRotation();
	if(LeftDoorRot.Yaw >= 0.f)
		m_LeftDoor->AddRelativeRotation(FRotator(0.f,-1.f,0.f));
	FRotator RightDoorRot = m_RightDoor->GetRelativeRotation();
	if(RightDoorRot.Yaw <= 0.f)
		m_RightDoor->AddRelativeRotation(FRotator(0.f,1.f,0.f));

	if(LeftDoorRot.Yaw <= 0.f && RightDoorRot.Yaw >= 0.f)
		GetWorldTimerManager().ClearTimer(m_TimerHandle);
}