// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoxTrigger.h"
#include "RoomTrigger.generated.h"



DECLARE_DELEGATE(FRoomEnterDeligate);
UCLASS()
class PROJECT1_API ARoomTrigger : public ABoxTrigger
{
	GENERATED_BODY()
	
	public:
	ARoomTrigger();
	
	protected:
	FRoomEnterDeligate m_RoomEnterDeligate;
	
	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;

	public:
	UFUNCTION()
	void TriggerBegin(AActor* _OtherActor);

	UFUNCTION()
	void TriggerEnd(AActor* _OtherActor);

	void SetTriggerSize(FVector SizeVector);

	FVector2D GetTriggerSize();
	
	template <class T>
	void SetRoomEnterDelegate(T* _Obj, void(T::* _Func)())
	{
		m_RoomEnterDeligate.BindUObject(_Obj, _Func);
	}
};
