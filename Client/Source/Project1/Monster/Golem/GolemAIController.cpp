// Fill out your copyright notice in the Description page of Project Settings.

#include "GolemAIController.h"

AGolemAIController::AGolemAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITreeAsset(TEXT("BehaviorTree'/Game/01Resources/Monster/Golem/BTGolem.BTGolem'"));
	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData>	BlackboardAsset(TEXT("BlackboardData'/Game/01Resources/Monster/BBMonster.BBMonster'"));
	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}

void AGolemAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGolemAIController::OnUnPossess()
{
	Super::OnUnPossess();
}