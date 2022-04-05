// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "SelectCharacterMainWidgetObejct.generated.h"

UCLASS()
class PROJECT1_API ASelectCharacterMainWidgetObejct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectCharacterMainWidgetObejct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	public:
	UFUNCTION(BlueprintCallable)
	class USelectCharacterMainWidget* GetSelectCharacterMainWidget();

};
