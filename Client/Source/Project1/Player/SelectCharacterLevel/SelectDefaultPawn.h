// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/DefaultPawn.h"
#include "SelectDefaultPawn.generated.h"

UCLASS()
class PROJECT1_API ASelectDefaultPawn : public ADefaultPawn
{
	GENERATED_BODY()
	
	public:
	// Sets default values for this pawn's properties
	ASelectDefaultPawn();

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Camera;

};
