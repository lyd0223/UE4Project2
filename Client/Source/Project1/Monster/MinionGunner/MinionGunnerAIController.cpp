
#include "MinionGunnerAIController.h"


AMinionGunnerAIController::AMinionGunnerAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITreeAsset(TEXT("BehaviorTree'/Game/01Resources/Monster/MinionGunner/BTMinionGunner.BTMinionGunner'"));
	if (AITreeAsset.Succeeded())
		m_AITree = AITreeAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UBlackboardData>	BlackboardAsset(TEXT("BlackboardData'/Game/01Resources/Monster/BBMonster.BBMonster'"));
	if (BlackboardAsset.Succeeded())
		m_AIBlackboard = BlackboardAsset.Object;
}

void AMinionGunnerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMinionGunnerAIController::OnUnPossess()
{
	Super::OnUnPossess();
}