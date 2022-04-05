// Fill out your copyright notice in the Description page of Project Settings.


#include "RampageAIController.h"


ARampageAIController::ARampageAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITreeAsset(TEXT("BehaviorTree'/Game/01Resources/Monster/BossMonster/Rampage/BTRampage.BTRampage'"));
	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData>	BlackboardAsset(TEXT("BlackboardData'/Game/01Resources/Monster/BBMonster.BBMonster'"));
	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}

void ARampageAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ARampageAIController::OnUnPossess()
{
	Super::OnUnPossess();
}