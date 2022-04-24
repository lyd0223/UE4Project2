#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Character.h"
#include "OtherPlayerCharacter.generated.h"

UCLASS()
class PROJECT1_API AOtherPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	int m_UserIdx;
	
public:
	AOtherPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(FVector& _Pos, FRotator const& _Rot);
};
