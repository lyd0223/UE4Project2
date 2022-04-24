// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherPlayerCharacter.h"

#include "AIController.h"

// Sets default values
AOtherPlayerCharacter::AOtherPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOtherPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOtherPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOtherPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AOtherPlayerCharacter::Move(FVector& _Pos, FRotator const& _Rot)
{
	AAIController* AIController = Cast<AAIController>(Controller);
	AIController->MoveToLocation(_Pos);

	FVector Dir = _Pos - GetActorLocation();
	SetActorRotation(_Rot);
}