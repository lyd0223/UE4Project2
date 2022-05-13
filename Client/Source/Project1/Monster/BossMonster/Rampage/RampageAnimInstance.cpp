// Fill out your copyright notice in the Description page of Project Settings.


#include "RampageAnimInstance.h"

#include "Rampage.h"


void URampageAnimInstance::AnimNotify_AttachEnd()
{
	ARampage* Owner = Cast<ARampage>(TryGetPawnOwner());
	if(Owner ==nullptr)
		return;
	Owner->Skill3RockDetach();
	
	
}
