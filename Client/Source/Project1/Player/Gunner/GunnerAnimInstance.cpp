#include "GunnerAnimInstance.h"

#include "Project1/Player/PlayerCharacter.h"
#include "Gunner.h"

UGunnerAnimInstance::UGunnerAnimInstance()
{
	
}


void UGunnerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UGunnerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	
}


void UGunnerAnimInstance::AnimNotify_Fire()
{
	AGunner* gunner = Cast<AGunner>(TryGetPawnOwner());

	gunner->FireNormalAttackBullet();
}

