// Fill out your copyright notice in the Description page of Project Settings.


#include "BelicaAnimInstance.h"

#include "Belica.h"


UBelicaAnimInstance::UBelicaAnimInstance()
{
	
}


void UBelicaAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UBelicaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	
}


void UBelicaAnimInstance::AnimNotify_NormalBullet()
{
	ABelica* Player = Cast<ABelica>(TryGetPawnOwner());

	Player->FireNormalBullet();
}

void UBelicaAnimInstance::AnimNotify_TrippleBullet()
{
	ABelica* Player = Cast<ABelica>(TryGetPawnOwner());

	Player->FireTrippleBullet();
}

void UBelicaAnimInstance::AnimNotify_RecoveryBullet()
{
	ABelica* Player = Cast<ABelica>(TryGetPawnOwner());

	Player->FireRecoveryBullet();
}

void UBelicaAnimInstance::AnimNotify_PowerBullet()
{
	ABelica* Player = Cast<ABelica>(TryGetPawnOwner());

	Player->FirePowerBullet();
}
