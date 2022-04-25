#pragma once

#include "../../GameInfo.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "OtherPlayerCharacter.generated.h"

UCLASS()
class PROJECT1_API AOtherPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	int m_UserIdx;
	
	//NicknameWidget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* m_NicknameWidgetComponent;

	TSubclassOf<UUserWidget> m_NicknameWidgetClass;
	
	class UPlayerAnimInstance* m_AnimInstance;
public:
	AOtherPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(FVector& _Pos, FRotator const& _Rot);
};
