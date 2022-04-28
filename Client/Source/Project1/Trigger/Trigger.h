// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"


UENUM(BlueprintType)
enum class ETriggerType : uint8
{
	Box,
	Sphere,
	Capsule
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggerDelegate, AActor*, _Actor);

UCLASS()
class PROJECT1_API ATrigger : public AActor
{
	GENERATED_BODY()
	
	public:	
	ATrigger();

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UShapeComponent* m_Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ETriggerType	m_ShapeType;

	FTriggerDelegate	m_TriggerBeginDelegate;
	FTriggerDelegate	m_TriggerEndDelegate;
	
	public:
	FTriggerDelegate& GetBeginDelegate()
	{
		return m_TriggerBeginDelegate;
	}

	FTriggerDelegate& GetEndDelegate()
	{
		return m_TriggerEndDelegate;
	}

	protected:
	virtual void BeginPlay() override;

	public:	
	virtual void Tick(float DeltaTime) override;

	public:
	UFUNCTION()
	void TriggerBeginOverlap(UPrimitiveComponent* OverlapCom, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

};
