// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerDetect.h"
#include "../Monster.h"
#include "../MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerDetect::UBTService_PlayerDetect()
{
	NodeName = TEXT("PlayerDetect");
	Interval = 0.5f;
}

void UBTService_PlayerDetect::TickNode(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return;

	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();

	// 유저 탐색.
	FCollisionQueryParams	params(NAME_None, false, Monster);
	FHitResult	HitResult;
	bool Sweep = GetWorld()->SweepSingleByChannel(HitResult,
		Monster->GetActorLocation(),
		Monster->GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8, 
		FCollisionShape::MakeSphere(MonsterInfo.TraceDistance),
		params);


	//디버그용 드로우
	// #if ENABLE_DRAW_DEBUG
	//
	// FColor	DrawColor = Sweep ? FColor::Red : FColor::Green;
	//
	// DrawDebugSphere(GetWorld(), Monster->GetActorLocation(),
	// 	MonsterInfo.TraceDistance/2, 20, DrawColor, false,
	// 	0.3f);
	//
	// #endif


	
	if (Sweep)
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitResult.GetActor());
	
	else
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
}
