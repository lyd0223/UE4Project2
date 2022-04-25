// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherPlayerCharacter.h"

#include "AIController.h"
#include "Project1/Player/PlayerAnimInstance.h"

// Sets default values
AOtherPlayerCharacter::AOtherPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//NicknameWidget
	m_NicknameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NicknameWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> NicknameWidgetClass
	(TEXT("WidgetBlueprint'/Game/01Resources/UI/WaitingRoomLevel/UI_CharacterNicknameWidget.UI_CharacterNicknameWidget_C'"));
	if(NicknameWidgetClass.Succeeded())
		m_NicknameWidgetClass = NicknameWidgetClass.Class;
	m_NicknameWidgetComponent->SetWidgetClass(m_NicknameWidgetClass);
	m_NicknameWidgetComponent->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AOtherPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	m_AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AOtherPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOtherPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AOtherPlayerCharacter::Move(FVector& _Pos, FRotator const& _Rot)
{
	
	SetActorRotation(_Rot);

	FVector Dir = _Pos - GetActorLocation();
	float Dot = FVector::DotProduct(GetActorForwardVector(),Dir);
	
	//목표지점과 현재 바라보는방향 사잇각구하기
	float RadianAngle = FMath::Acos(Dot);
	float DegreesAngle = FMath::RadiansToDegrees(RadianAngle);

	//방향 구하기 (Cross Product한 값이 0보다 작을시 왼쪽.)
	FVector Cross = FVector::CrossProduct(GetActorForwardVector(),Dir);
	if(Cross.Z < 0)
	{
		DegreesAngle *= -1.f;
	}
	m_AnimInstance->SetDirection(DegreesAngle);
	
	AAIController* AIController = Cast<AAIController>(Controller);
	AIController->MoveToLocation(_Pos);
}