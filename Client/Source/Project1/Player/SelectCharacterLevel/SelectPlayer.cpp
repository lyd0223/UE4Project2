// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayer.h"
#include "SelectPlayerAnimInstance.h"
#include "Project1/Player/SelectCharacterPlayerController.h"

// Sets default values
ASelectPlayer::ASelectPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_PlayerJob = EPlayerJob::End;
	m_Mesh = nullptr;
	
}

// Called when the game starts or when spawned
void ASelectPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetSkeletalMesh(m_Mesh);

	FVector Pos = GetMesh()->GetRelativeLocation();
	Pos.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	GetMesh()->SetRelativeLocation(Pos);
	
	m_AnimInstance = Cast<USelectPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	
	ASelectCharacterPlayerController* PlayerController = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
	if(PlayerController)
	{
		PlayerController->AddSelectCharacter(this);
	}
}

// Called every frame
void ASelectPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelectPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

