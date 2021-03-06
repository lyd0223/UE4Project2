
#include "Monster.h"

#include "DamageFloating.h"
#include "MonsterAIController.h"
#include "MonsterAnimInstance.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Project1GameModeBase.h"
#include "../UI/MainHUDWidget.h"
#include "../Player/PlayerCharacter.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SpawnPoint = nullptr;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetCanBeDamaged(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetMesh()->bReceivesDecals = false;
	
	m_AttackEnd = true;

	m_Target = nullptr;
	
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	UProject1GameInstance* gameInst = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	if(gameInst)
	{
		const FMonsterTableInfo* Info = gameInst->FindMonsterInfo(m_MonsterInfoName);

		if (Info)
		{
			m_MonsterInfo.Name = Info->Name;
			m_MonsterInfo.Attack = Info->Attack;
			m_MonsterInfo.Armor = Info->Armor;
			m_MonsterInfo.HP = Info->HP;
			m_MonsterInfo.HPMax = Info->HPMax;
			m_MonsterInfo.MP = Info->MP;
			m_MonsterInfo.MPMax = Info->MPMax;
			m_MonsterInfo.Level = Info->Level;
			m_MonsterInfo.Exp = Info->Exp;
			m_MonsterInfo.Gold = Info->Gold;
			m_MonsterInfo.AttackDistance = Info->AttackDistance;
			m_MonsterInfo.AttackSpeed = Info->AttackSpeed;
			m_MonsterInfo.AttackAngle = Info->AttackAngle;
			m_MonsterInfo.MoveSpeed = Info->MoveSpeed;
			m_MonsterInfo.TraceDistance = Info->TraceDistance;
		}
	}
	m_AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMonster::TakeDamage(float DamageAmount, 
	struct FDamageEvent const& DamageEvent, 
	class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Damage == 0.f)
		return 0.f;

	Damage = Damage - m_MonsterInfo.Armor;
	Damage = Damage < 1.f ? 1.f : Damage;

	m_MonsterInfo.HP -= Damage;

	//????????? ????????? ??????
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	int32 RandY = FMath::RandRange(0, 100);
	int32 RandZ = FMath::RandRange(0, 50);
	FVector FloatingLoc = GetActorLocation() + FVector(0.f, (float)RandY, (float)RandZ);
	ADamageFloating* DamageFloating = GetWorld()->SpawnActor<ADamageFloating>(ADamageFloating::StaticClass(), FloatingLoc, GetActorRotation(), param);
	DamageFloating->SetDamage(Damage);
	
	// UI ????????? ?????? ??????
	AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameModeBase)
	{
		UMonsterStateWidget* MonsterStateWidget = GameModeBase->GetMainHUDWidget()->GetMonsterStateWidget();
		MonsterStateWidget->SetDatas(m_MonsterInfo);
	}
	
	// ???????????? ????????? ??????
	if (m_MonsterInfo.HP <= 0)
	{
		//No more collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//Change Anim
		m_AnimInstance->ChangeAnimType(EMonsterAnimType::Death);

		//AI controller off
		AMonsterAIController* MonsterController = Cast<AMonsterAIController>(GetController());
		
		if (MonsterController)
			MonsterController->BrainComponent->StopLogic(TEXT("Dead"));

		//Player EXP??????
		APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		Player->EarnEXP(m_MonsterInfo.Exp);
		
	}

	return Damage;
}

void AMonster::Death()
{
	// ???????????? ????????? ????????? ????????????.
	// ??????????????? ????????? ????????? ?????? ?????? ????????????.
	// ????????? ????????????.

	//override??? ??????????????? ??????.
}

void AMonster::NormalAttack()
{
	
}


void AMonster::UseSkill(int32 Index)
{
	
}