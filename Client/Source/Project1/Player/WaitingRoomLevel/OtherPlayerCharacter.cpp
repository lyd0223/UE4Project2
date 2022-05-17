// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherPlayerCharacter.h"

#include "AIController.h"
#include "Project1/Player/PlayerAnimInstance.h"
#include "Project1/UI/WaitingRoomLevel/CharacterNicknameWidget.h"

// Sets default values
AOtherPlayerCharacter::AOtherPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//NicknameWidget
	m_NicknameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NicknameWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> NicknameWidgetClass
	(TEXT(
		"WidgetBlueprint'/Game/01Resources/UI/WaitingRoomLevel/UI_CharacterNicknameWidget.UI_CharacterNicknameWidget_C'"));
	if (NicknameWidgetClass.Succeeded())
		m_NicknameWidgetClass = NicknameWidgetClass.Class;
	m_NicknameWidgetComponent->SetWidgetClass(m_NicknameWidgetClass);
	m_NicknameWidgetComponent->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AOtherPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	UCharacterNicknameWidget* CharacterNicknameWidget = Cast<UCharacterNicknameWidget>(
		m_NicknameWidgetComponent->GetWidget());
	if (CharacterNicknameWidget == nullptr)
		return;
	CharacterNicknameWidget->SetDelegate(this, &AOtherPlayerCharacter::NickNameWidgetCallBackFunc);

}

// Called every frame
void AOtherPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOtherPlayerCharacter::Move(const FVector& _Pos, const FRotator& _Rot)
{
	//방향회전
	SetActorRotation(_Rot);
	
	FVector Dir = _Pos - GetActorLocation();
	if(Dir.Size() < 1.f)
	{
		m_AnimInstance->SetDirection(0.f);
		return;
	}
	
	//목표지점과 현재 바라보는방향 사잇각구하기
	float Dot = FVector::DotProduct(GetActorForwardVector(), Dir);
	float RadianAngle = FMath::Acos(Dot);
	float DegreesAngle = FMath::RadiansToDegrees(RadianAngle);

	//방향 구하기 (Cross Product한 값이 0보다 작을시 왼쪽.)
	FVector Cross = FVector::CrossProduct(GetActorForwardVector(), Dir);
	if (Cross.Z < 0)
		DegreesAngle *= -1.f;
	m_AnimInstance->SetDirection(DegreesAngle);

	SetActorLocation(_Pos);
}

void AOtherPlayerCharacter::NickNameWidgetCallBackFunc()
{
	UCharacterNicknameWidget* CharacterNicknameWidget = Cast<UCharacterNicknameWidget>(
		m_NicknameWidgetComponent->GetWidget());
	if (CharacterNicknameWidget == nullptr)
		return;
	
	FString Nickname = TEXT("");
	UClientBlueprintFunctionLibrary::UTF8ToFString(m_CharacterInfo.m_Nickname, Nickname);
	CharacterNicknameWidget->SetNicknameText(Nickname);
}