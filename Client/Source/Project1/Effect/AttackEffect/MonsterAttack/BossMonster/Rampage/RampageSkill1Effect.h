#pragma once

#include "Project1/GameInfo.h"
#include "Project1/Effect/AttackEffect/AttackEffect.h"
#include "RampageSkill1Effect.generated.h"


UCLASS()
class PROJECT1_API ARampageSkill1Effect : public AAttackEffect
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARampageSkill1Effect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack() override;
};
