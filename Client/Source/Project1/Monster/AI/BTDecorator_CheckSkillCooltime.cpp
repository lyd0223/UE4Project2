// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckSkillCooltime.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTDecorator_CheckSkillCooltime::UBTDecorator_CheckSkillCooltime()
{
	NodeName = TEXT("CheckSkillCooltime");
	
	m_MaxTime = 10.f;

	bNotifyActivation = true;

}

void UBTDecorator_CheckSkillCooltime::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	UWorld* world = GetWorld();
}

bool UBTDecorator_CheckSkillCooltime::CalculateRawConditionValue(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!Controller)
		return false;

	AMonster* Monster = Cast<AMonster>(Controller->GetPawn());

	if (!Monster)
		return false;
	
	const FMonsterInfo& MonsterInfo = Monster->GetMonsterInfo();


	// if(m_ACCTime >=  m_MaxTime)
	// {
	// 	return true;
	// }
	return true;
}
