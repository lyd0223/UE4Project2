// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Skill.h"
#include "../MonsterAIController.h"
#include "../BossMonster/BossMonster.h"
#include "../../Player/PlayerCharacter.h"
#include "../MonsterAnimInstance.h"

UBTTaskNode_Skill::UBTTaskNode_Skill()
{
	NodeName = TEXT("Skill");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Skill::ExecuteTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!Controller)
		return EBTNodeResult::Failed;

	ABossMonster* BossMonster = Cast<ABossMonster>(Controller->GetPawn());
	if (!BossMonster)
		return EBTNodeResult::Failed;

	APlayerCharacter* Target = Cast<APlayerCharacter>(
		Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!Target)
	{
		BossMonster->GetAnim()->ChangeAnimType(EMonsterAnimType::Idle);

		Controller->StopMovement();
		return EBTNodeResult::Failed;
	}


	
	if(BossMonster->GetIsSkillOn())
	{
		BossMonster->SetTarget(Target);
		//몬스터 회전
		FVector MonsterLoc = BossMonster->GetActorLocation();
		FVector TargetLoc = Target->GetActorLocation();
		FVector Dir = TargetLoc - MonsterLoc;
		Dir.Normalize();
		BossMonster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));

		//몬스터 애니메이션
		BossMonster->GetAnim()->ChangeAnimType(EMonsterAnimType::Skill);

		//스킬발동
		int32 SkillIndex = FMath::RandRange(0,2);
		BossMonster->UseSkill(SkillIndex);
		BossMonster->SetIsSkillOn(false);
	}
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTaskNode_Skill::AbortTask(
	UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp, NodeMemory);

	return result;
}

void UBTTaskNode_Skill::TickTask(UBehaviorTreeComponent& OwnerComp,
                                        uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ABossMonster* BossMonster = Cast<ABossMonster>(Controller->GetPawn());
	if (!BossMonster)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	//PrintViewport(1.f, FColor::Red, TEXT("NormalAttack AttackStart"));


	APlayerCharacter* Target = Cast<APlayerCharacter>(
		Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!Target)
	{
		BossMonster->GetAnim()->ChangeAnimType(EMonsterAnimType::Idle);

		Controller->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	const FMonsterInfo& MonsterInfo = BossMonster->GetMonsterInfo();

	FVector MonsterLoc = BossMonster->GetActorLocation();
	FVector TargetLoc = Target->GetActorLocation();

	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);


	if (BossMonster->GetAttackEnd())
	{
		if (Distance > MonsterInfo.TraceDistance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		
		else
		{
			FVector Dir = TargetLoc - MonsterLoc;
			Dir.Normalize();

			BossMonster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		}
		
		BossMonster->SetAttackEnd(false);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
