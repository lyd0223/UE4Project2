// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectDefaultPawn.h"

ASelectDefaultPawn::ASelectDefaultPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	m_Camera->SetupAttachment(RootComponent);

	m_Camera->SetRelativeLocation(FVector(200.f, 0.f, 80.f));
	
	GetMeshComponent()->SetVisibility(false);
}
