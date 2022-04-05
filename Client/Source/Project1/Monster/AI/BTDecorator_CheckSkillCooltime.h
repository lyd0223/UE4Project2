// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckSkillCooltime.generated.h"




UCLASS()
class PROJECT1_API UBTDecorator_CheckSkillCooltime : public UBTDecorator
{
	GENERATED_BODY()
	
	public:
	UBTDecorator_CheckSkillCooltime();

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_CheckType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_MaxTime;
	
	protected:
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
