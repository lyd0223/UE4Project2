// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBox.h"

#include "Project1/Project1GameInstance.h"
#include "Project1/Trigger/LootBoxTrigger.h"

// Sets default values
ALootBox::ALootBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	
	m_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	m_WidgetComponent->SetupAttachment(m_Mesh);
	
	m_WidgetComponent->SetVisibility(false);
	
	m_LootBoxTrigger = nullptr;

}

// Called when the game starts or when spawned
void ALootBox::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	m_LootBoxTrigger = GetWorld()->SpawnActor<ALootBoxTrigger>(ALootBoxTrigger::StaticClass(), GetActorLocation(),
														GetActorRotation(), param);
	m_LootBoxTrigger->SetTriggerSize(FVector(100.f, 100.f, 100.f));
	m_LootBoxTrigger->SetOwnerLootBox(this);

	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	uint8 RandNum1 = FMath::RandRange(0, 100);
	if (RandNum1 >= 50)
	{
		FItem* Item = new FItem();
		Item->ItemTableInfo = GameInstance->FindItemTableInfo(TEXT("분노의영약"));
		Item->Count = 1;

		this->GetDropItemArray().Add(Item);
	}
	uint8 RandNum2 = FMath::RandRange(0, 100);
	if (RandNum2 >= 50)
	{
		FItem* Item = new FItem();
		Item->ItemTableInfo = GameInstance->FindItemTableInfo(TEXT("속도의영약"));
		Item->Count = 1;

		this->GetDropItemArray().Add(Item);
	}
	uint8 RandNum3 = FMath::RandRange(0, 3);
	if(RandNum3 > 0)
	{
		FItem* Item = new FItem();
		Item->ItemTableInfo = GameInstance->FindItemTableInfo(TEXT("HP포션(소)"));
		Item->Count = RandNum3;
		this->GetDropItemArray().Add(Item);

	}
}

// Called every frame
void ALootBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

