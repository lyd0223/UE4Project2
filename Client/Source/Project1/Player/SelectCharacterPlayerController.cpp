// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterPlayerController.h"
#include "SelectCharacterLevel/SelectPlayer.h"
#include "SelectCharacterLevel/SelectPlayerAnimInstance.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ASelectCharacterPlayerController::ASelectCharacterPlayerController()
{
	bShowMouseCursor = true;
}


void ASelectCharacterPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void ASelectCharacterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}



void ASelectCharacterPlayerController::Move(EPlayerJob PlayerJob)
{
	//타겟 색인
	ASelectPlayer* Target = nullptr;
	for(auto SelectPlayer : m_SelectCharacterArray)
	{
		if(SelectPlayer->GetPlayerJob() == PlayerJob)
			Target = SelectPlayer;
	}
	
	//애니메이션 변경
	if(Target)
	{
		USelectPlayerAnimInstance* AnimInstance = Cast<USelectPlayerAnimInstance>(Target->GetAnimInstance());
		if(AnimInstance)
			AnimInstance->ChangeAnimType(ESelectPlayerAnimType::Select);
	}
	//컨트롤러 위치변경
	FVector Loc = Target->GetActorLocation() - Target->GetActorForwardVector() * 500.f;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Loc);

	//로테이션 변경
	
	Loc.Z = 0.f;
	FVector TargetLoc = Target->GetActorLocation();
	TargetLoc.Z = 0.f;
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(Loc, TargetLoc);
	GetPawn()->SetActorRotation(Rot);
	
}