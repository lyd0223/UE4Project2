// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "DamageFloating.generated.h"

UCLASS()
class PROJECT1_API ADamageFloating : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageFloating();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* m_WidgetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetDamage(int32 Damage);
};
