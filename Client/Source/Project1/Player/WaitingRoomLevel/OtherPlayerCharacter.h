#pragma once

#include "../../GameInfo.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Project1/Global/Message/ContentsStruct.h"
#include "OtherPlayerCharacter.generated.h"

UCLASS()
class PROJECT1_API AOtherPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOtherPlayerCharacter();

protected:
	FCharacterInfo m_CharacterInfo;

	//NicknameWidget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* m_NicknameWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> m_NicknameWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UPlayerAnimInstance* m_AnimInstance;

public:
	FCharacterInfo GetCharacterInfo() const
	{
		return m_CharacterInfo;
	}
	
	void SetCharacterInfo(const FCharacterInfo& _CharacterInfo)
	{
		m_CharacterInfo = _CharacterInfo;	
	}
	
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void Move(FVector& _Pos, FRotator const& _Rot);
	void NickNameWidgetCallBackFunc();
};
