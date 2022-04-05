// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "LootBox.generated.h"

UCLASS()
class PROJECT1_API ALootBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALootBox();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ALootBoxTrigger* m_LootBoxTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* m_WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* m_Mesh;

	UUserWidget* m_Widget;

	TArray<FItem*> m_DropItemArray;
	
public:
	UWidgetComponent* GetWidgetComponent() const
	{
		return m_WidgetComponent;
	}
	USkeletalMeshComponent* GetMesh() const
	{
		return m_Mesh;
	}
	TArray<FItem*>& GetDropItemArray()
	{
		return m_DropItemArray;
	}
	void AddDropItemArray(FItem* Item)
	{
		m_DropItemArray.Add(Item);
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
