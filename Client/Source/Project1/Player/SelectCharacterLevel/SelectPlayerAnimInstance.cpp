// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectPlayerAnimInstance.h"


USelectPlayerAnimInstance::USelectPlayerAnimInstance()
{
	m_AnimType = ESelectPlayerAnimType::Idle;
}
void USelectPlayerAnimInstance::ChangeAnimType(ESelectPlayerAnimType Type)
{
	
	m_AnimType = Type;
}
void USelectPlayerAnimInstance::AnimNotify_TransitionIdle()
{
	m_AnimType = ESelectPlayerAnimType::Idle;
}
