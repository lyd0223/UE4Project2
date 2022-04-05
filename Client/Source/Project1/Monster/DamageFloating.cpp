// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageFloating.h"

#include "Project1/UI/DamageFloating/DamageFloatingWidget.h"

// Sets default values
ADamageFloating::ADamageFloating()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("WidgetBlueprint'/Game/01Resources/UI/DamageFloating/UI_DamageFloating.UI_DamageFloating_C'"));
	if (WidgetAsset.Succeeded())
		m_WidgetComponent->SetWidgetClass(WidgetAsset.Class);
	
	m_WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	m_WidgetComponent->SetDrawSize(FVector2D(100.f, 50.f));
}

// Called when the game starts or when spawned
void ADamageFloating::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageFloating::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


void ADamageFloating::SetDamage(int32 Damage)
{
	UDamageFloatingWidget* Widget = Cast<UDamageFloatingWidget>(m_WidgetComponent->GetUserWidgetObject());
	Widget->SetDamageText(Damage);
	Widget->SetOwnerActor(this);
}


