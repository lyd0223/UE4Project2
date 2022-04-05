// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GhostCharacter.h"
#include "PlayerAnimInstance.h"
#include "SelectCharacterPlayerController.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Project1GameModeBase.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Manager/InventoryManager.h"
#include "Project1/UI/MainHUDWidget.h"
#include "Project1/Map/Room.h"
#include "Project1/UI/StatsWidget.h"
#include "Project1/UI/MenuCommonWidget.h"
#include "Project1/UI/QuickItemSlotWidget.h"
#include "WaitingRoomLevel/WaitingRoomPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


	//Camera
	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));

	m_Arm->SetupAttachment(GetMesh());
	m_Camera->SetupAttachment(m_Arm);

	// //Minimap Camera
	// m_MinimapSceneCapture2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MinimapSceneCaputre2D"));
	// m_MinimapSceneCapture2D->SetupAttachment(RootComponent);
	// m_MinimapSceneCapture2D->SetRelativeLocation(FVector(0.f,0.f,3000.f));
	// m_MinimapSceneCapture2D->SetRelativeRotation(FRotator(0.f,-90.f,0.f));

	m_AnimInstance = nullptr;

	m_MoveKey = false;
	m_AttackEnable = true;

	m_IsUIMode = false;

	m_IsWaitingRoom = false;
	
	//대쉬 리본트레일 효과
	m_TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticle"));
	m_TrailParticle->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<UParticleSystem> TrailAsset(TEXT("ParticleSystem'/Game/01Resources/Effect/PSPlayerDashTrail2.PSPlayerDashTrail2'"));
	if(TrailAsset.Succeeded())
		m_TrailParticle->SetTemplate(TrailAsset.Object);
	m_TrailParticle->SetVisibility(false);
	
	//대쉬 잔상효과
	m_GhostTrailTime = 0.1f;
	m_Mesh = nullptr;

	//콜리전설정
	GetCapsuleComponent()->SetCollisionProfileName("Player");
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//퀵슬롯
	m_BulletIndex = 0;

	for (int i = 0; i < 5; i++)
		m_ItemQuickSlotsArray.Add(nullptr);
	for (int i = 0; i < 4; i++)
		m_BulletQuickSlotsArray.Add(nullptr);

	//렌더타겟
	m_SceneCaputreComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	m_SceneCaputreComponent->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RTTextureAsset(TEXT("TextureRenderTarget2D'/Game/01Resources/Player/RTPlayer.RTPlayer'"));
	if(RTTextureAsset.Succeeded())
		m_SceneCaputreComponent->TextureTarget = RTTextureAsset.Object;
	m_SceneCaputreComponent->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	m_SceneCaputreComponent->SetRelativeLocation(FVector(0.f,150.f,110.f));
	m_SceneCaputreComponent->SetRelativeRotation(FRotator(0.f,0.f,-90.f));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UProject1GameInstance* gameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	gameInstance->GetInventoryManager()->SetOwnerCharacter(this);
	
	const FPlayerTableInfo* info = gameInstance->FindPlayerInfo(m_JobName);

	if (info)
	{
		m_PlayerInfo.Name = info->Name;
		m_PlayerInfo.Job = info->Job;
		m_PlayerInfo.CharacterTexture = info->CharacterTexture;
		m_PlayerInfo.ATK = info->ATK;
		m_PlayerInfo.DEF = info->DEF;
		m_PlayerInfo.HP = info->HP;
		m_PlayerInfo.HPMax = info->HPMax;
		m_PlayerInfo.SP = info->SP;
		m_PlayerInfo.SPMax = info->SPMax;
		m_PlayerInfo.Level = info->Level;
		m_PlayerInfo.EXP = info->EXP;
		m_PlayerInfo.EXPMax = info->EXPMax;
		m_PlayerInfo.Gold = info->Gold;
		m_PlayerInfo.AttackDistance = info->AttackDistance;
		m_PlayerInfo.AttackSpeed = info->AttackSpeed;
		m_PlayerInfo.AttackAngle = info->AttackAngle;
		m_PlayerInfo.MoveSpeed = info->MoveSpeed;
	}

	//UI 변경
	SetUI();

	//미니맵에서 쓰기위한 몬스터,룸,도어 탐지를 위한 셋타이머.
	GetWorld()->GetTimerManager().SetTimer(m_DetectMonsterHandle, this, &APlayerCharacter::DetectMonster, 0.1f, true);
	GetWorld()->GetTimerManager().SetTimer(m_DetectRoomHandle, this, &APlayerCharacter::DetectRoom, 0.1f, true);
	GetWorld()->GetTimerManager().SetTimer(m_DetectDoorHandle, this, &APlayerCharacter::DetectDoor, 0.1f, true);

	//SP 회복을 위한 셋타이머
	GetWorld()->GetTimerManager().SetTimer(m_SPRecoveryHandle, this, &APlayerCharacter::SPRecovery, 1.f, true);

	//스폰 이펙트
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
	                                                              GetActorLocation(), FRotator::ZeroRotator, param);

	Effect->LoadParticleAsync(TEXT("PlayerSpawn"));
	Effect->LoadSoundAsync(TEXT("PlayerSpawn"));
	
	m_SceneCaputreComponent->ShowOnlyActors.Add(this);


}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &APlayerCharacter::MoveFrontKey);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRightKey);
	PlayerInputComponent->BindAxis(TEXT("RotationZ"), this, &APlayerCharacter::RotationZKey);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &APlayerCharacter::CameraZoomKey);
	PlayerInputComponent->BindAxis(TEXT("CameraRotationY"), this, &APlayerCharacter::CameraRotationYKey);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::JumpKey);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::AttackKey);
	PlayerInputComponent->BindAction(TEXT("Menu"), EInputEvent::IE_Pressed, this, &APlayerCharacter::MenuKey);
	PlayerInputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Pressed, this, &APlayerCharacter::DashKey);
	PlayerInputComponent->BindAction(TEXT("BulletQuickSlotLeft"), EInputEvent::IE_Pressed, this,
	                                 &APlayerCharacter::BulletQuickSlotLeftKey);
	PlayerInputComponent->BindAction(TEXT("BulletQuickSlotRight"), EInputEvent::IE_Pressed, this,
	                                 &APlayerCharacter::BulletQuickSlotRightKey);
	PlayerInputComponent->BindAction(TEXT("ItemQuickSlot1"), EInputEvent::IE_Pressed, this,
	                                 &APlayerCharacter::ItemQuickSlot1Key);
	PlayerInputComponent->BindAction(TEXT("ItemQuickSlot2"), EInputEvent::IE_Pressed, this,
	                                 &APlayerCharacter::ItemQuickSlot2Key);
	PlayerInputComponent->BindAction(TEXT("ItemQuickSlot3"), EInputEvent::IE_Pressed, this,
	                                 &APlayerCharacter::ItemQuickSlot3Key);
	PlayerInputComponent->BindAction(TEXT("ItemQuickSlot4"), EInputEvent::IE_Pressed, this,
	                                 &APlayerCharacter::ItemQuickSlot4Key);
	PlayerInputComponent->BindAction(TEXT("ItemQuickSlot5"), EInputEvent::IE_Pressed, this,
	                                 &APlayerCharacter::ItemQuickSlot5Key);
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                   class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Damage == 0.f)
		return 0.f;

	Damage = Damage - m_PlayerInfo.DEF;
	Damage = Damage < 1.f ? 1.f : Damage;

	m_PlayerInfo.HP -= Damage;

	// �÷��̾ �׾��� ���
	if (m_PlayerInfo.HP <= 0)
	{
		m_AnimInstance->ChangeAnimType(EPlayerAnimType::Death);
	}
	else
	{
		m_AnimInstance->SetHit(true);
	}

	//UMG 체력 변경
	AProject1GameModeBase* gameMode = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	if (IsValid(gameMode))
	{
		UMainHUDWidget* mainHUDWidget = gameMode->GetMainHUDWidget();

		if (IsValid(mainHUDWidget))
		{
			UPlayerHUDWidget* playerHUDWidget = mainHUDWidget->GetPlayerHUDWidget();

			if (IsValid(playerHUDWidget))
			{
				playerHUDWidget->SetHPPercent(m_PlayerInfo.HP / (float)m_PlayerInfo.HPMax);
				playerHUDWidget->SetHPText(FString::Printf(TEXT("%d / %d"), m_PlayerInfo.HP, m_PlayerInfo.HPMax));
			}
		}
	}

	// GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(
	// 	UHitCameraShake::StaticClass());


	return Damage;
}


void APlayerCharacter::MoveFrontKey(float Scale)
{
	if (!m_IsUIMode)
	{
		AddMovementInput(GetActorForwardVector(), Scale);

		if (Scale == 0.f)
		{
			m_MoveKey = false;
			m_AnimInstance->SetDirection(0.f);
		}
		else if (Scale == 1.f)
		{
			m_MoveKey = true;
			m_AnimInstance->SetDirection(0.f);
		}
		else
		{
			m_MoveKey = true;
			m_AnimInstance->SetDirection(180.f);
		}
	}
}

void APlayerCharacter::MoveRightKey(float Scale)
{
	if (!m_IsUIMode)
	{
		AddMovementInput(GetActorRightVector(), Scale);
		float Direction = m_AnimInstance->GetDirection();

		if (Scale == 1.f)
		{
			m_MoveKey = true;
			if (Direction == 0.f)
				m_AnimInstance->SetDirection(45.f);

			else
				m_AnimInstance->SetDirection(135.f);
		}
		else if (Scale == -1.f)
		{
			m_MoveKey = true;
			if (Direction == 0.f)
				m_AnimInstance->SetDirection(-45.f);

			else
				m_AnimInstance->SetDirection(-135.f);
		}
	}
}

void APlayerCharacter::RotationZKey(float Scale)
{
	if (!m_IsUIMode)
	{
		if (m_IsWaitingRoom)
		{
			// AWaitingRoomPlayerController* WaitingRoomPlayerController =
			// 	Cast<AWaitingRoomPlayerController>(GetWorld()->GetFirstPlayerController());
			//
			// if(WaitingRoomPlayerController)
			// {
			// 	WaitingRoomPlayerController->AddYawInput(Scale);
			// }
			if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::RightMouseButton))
				AddControllerYawInput(Scale);
		}
		else
		{
			AddControllerYawInput(Scale);

			//미니맵 회전
			if (Scale != 0.f)
			{
				AProject1GameModeBase* gameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
				if (gameModeBase)
				{
					UMinimapWidget* minimapWidget = gameModeBase->GetMainHUDWidget()->GetMinimapWidget();
					if (minimapWidget)
					{
						minimapWidget->RotateMinimap(GetActorRotation().Yaw);
					}
				}
			}
		}
	}
}

void APlayerCharacter::CameraZoomKey(float Scale)
{
	m_Arm->TargetArmLength -= Scale * 20.f;

	if (m_Arm->TargetArmLength < 100.f)
		m_Arm->TargetArmLength = 100.f;

	else if (m_Arm->TargetArmLength > 300.f)
		m_Arm->TargetArmLength = 300.f;
}

void APlayerCharacter::CameraRotationYKey(float Scale)
{
	if (!m_IsUIMode)
	{
		FRotator Rot = m_Arm->GetRelativeRotation();

		Rot.Pitch += Scale * 100.f * GetWorld()->GetDeltaSeconds();

		if (Rot.Pitch > 30.f)
			Rot.Pitch = 30.f;

		else if (Rot.Pitch < -45.f)
			Rot.Pitch = -45.f;

		m_Arm->SetRelativeRotation(Rot);

		m_AnimInstance->SetPitch(Rot.Pitch);
	}
}

void APlayerCharacter::JumpKey()
{
	// if (m_Death)
	// 	return;
	//

	if (m_AnimInstance->GetAnimType() == EPlayerAnimType::Ground)
	{
		Jump();

		m_AnimInstance->ChangeAnimType(EPlayerAnimType::Jump);
	}
}

void APlayerCharacter::AttackKey()
{
	if (!m_IsWaitingRoom)
	{
		if (m_AttackEnable && !m_IsUIMode)
		{
			m_AttackEnable = false;
			Attack();
		}
	}
	else
	{
		AWaitingRoomPlayerController* PlayerController = Cast<AWaitingRoomPlayerController>(GetController());
		PlayerController->OpenWidget();
	}
}

void APlayerCharacter::MenuKey()
{
	if (!m_IsWaitingRoom)
	{
		AProject1GameModeBase* gameMode = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (gameMode)
		{
			UMainHUDWidget* MainHUDWidget = Cast<UMainHUDWidget>(gameMode->GetMainHUDWidget());
			if (MainHUDWidget)
			{
				UMenuWidget* MenuWidget = Cast<UMenuWidget>(MainHUDWidget->GetMenuWidget());
				if (MenuWidget)
				{
					APlayerController* playerController = Cast<APlayerController>(Controller);
					if (MenuWidget->GetVisibility() == ESlateVisibility::Collapsed)
					{
						MenuWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
						playerController->bShowMouseCursor = true;
						m_IsUIMode = true;
					}
					else
					{
						MenuWidget->SetVisibility(ESlateVisibility::Collapsed);
						playerController->bShowMouseCursor = false;
						m_IsUIMode = false;
					}
					FActorSpawnParameters param;
					param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), GetActorLocation(),
						FRotator::ZeroRotator, param);
					Effect->LoadSoundAsync(TEXT("OpenWidget"));
					Effect->SetLifeTime(1.f);
				}
			}
		}
	}
}

void APlayerCharacter::DashKey()
{
	if (!m_IsWaitingRoom && !m_IsUIMode)
	{
		if (m_AnimInstance->GetAnimType() == EPlayerAnimType::Ground)
		{
			m_AnimInstance->ChangeAnimType(EPlayerAnimType::Dash);
			m_AttackEnable = false;

			float DirAngle = m_AnimInstance->GetDirection();

			FVector FowardVector = GetActorForwardVector();
			FowardVector.Normalize();
			FowardVector = FowardVector.FVector::RotateAngleAxis(DirAngle, FVector::UpVector);

			float dashPower = 3000.f;

			LaunchCharacter(FowardVector * dashPower, false, false);

			m_PlayerInfo.SP -= 10;

			//Dash TrailRender
			m_TrailParticle->SetVisibility(true);
			//Dash GhostTrail
			GhostTrailFunc();
			
			//UMG 기력 변경
			AProject1GameModeBase* gameMode = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
			if (IsValid(gameMode))
			{
				UMainHUDWidget* mainHUDWidget = gameMode->GetMainHUDWidget();

				if (IsValid(mainHUDWidget))
				{
					UPlayerHUDWidget* playerHUDWidget = mainHUDWidget->GetPlayerHUDWidget();

					if (IsValid(playerHUDWidget))
					{
						playerHUDWidget->SetSPPercent(m_PlayerInfo.SP / (float)m_PlayerInfo.SPMax);
						playerHUDWidget->SetSPText(
							FString::Printf(TEXT("%d / %d"), m_PlayerInfo.SP, m_PlayerInfo.SPMax));
					}
				}
			}
		}
	}
}

void APlayerCharacter::BulletQuickSlotLeftKey()
{
	if (!m_IsWaitingRoom && !m_IsUIMode)
	{
		AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (IsValid(GameModeBase))
		{
			UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();
			if (IsValid(MainHUDWidget))
			{
				UQuickSlotsWidget* QuickSlotsWidget = MainHUDWidget->GetQuickSlotWidget();
				if (IsValid(QuickSlotsWidget))
				{
					if (m_BulletIndex > 0)
					{
						QuickSlotsWidget->QuickBulletSlotChange(EQuickBulletSlotChangeType::Left, m_BulletIndex);
						m_BulletIndex--;
					}
				}
			}
		}
	}
}

void APlayerCharacter::BulletQuickSlotRightKey()
{
	GetWorld()->ForceGarbageCollection(true);
	if (!m_IsWaitingRoom && !m_IsUIMode)
	{
		AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (IsValid(GameModeBase))
		{
			UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();
			if (IsValid(MainHUDWidget))
			{
				UQuickSlotsWidget* QuickSlotsWidget = MainHUDWidget->GetQuickSlotWidget();
				if (IsValid(QuickSlotsWidget))
				{
					if (m_BulletIndex < 3)
					{
						QuickSlotsWidget->QuickBulletSlotChange(EQuickBulletSlotChangeType::Right, m_BulletIndex);
						m_BulletIndex++;
					}
				}
			}
		}
	}
}

void APlayerCharacter::ItemQuickSlot1Key()
{
	if (!m_IsWaitingRoom && !m_IsUIMode)
	{
		UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());

		if (IsValid(GameInstance))
		{
			if (m_ItemQuickSlotsArray[0])
			{
				GameInstance->GetInventoryManager()->DeductItem(m_ItemQuickSlotsArray[0]);
				AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
				if (IsValid(GameModeBase))
				{
					//QuickSlot 갯수변경
					UQuickItemSlotWidget* QuickItemSlotWidget = GameModeBase->GetMainHUDWidget()->GetQuickSlotWidget()->
					                                                          GetQuickItemSlotWidget(0);
					QuickItemSlotWidget->SlotRefresh(m_ItemQuickSlotsArray[0]->Count);
					//인벤토리 갯수변경
					UInventoryWidget* InventoryWidget = GameModeBase->GetMainHUDWidget()->GetMenuWidget()->
																	GetInventoryWidget();
					InventoryWidget->DeductItemCount(m_ItemQuickSlotsArray[0]);
				}
			}
			else //0번 아이템퀵슬롯이 비어잇을때
			{
				//PrintViewport(2.f, FColor::Yellow, TEXT("1번 슬롯이 비어있습니다"));
			}
		}
	}
}

void APlayerCharacter::ItemQuickSlot2Key()
{
	if (!m_IsWaitingRoom && !m_IsUIMode)
	{
		UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());

		if (IsValid(GameInstance))
		{
			if (m_ItemQuickSlotsArray[1])
			{
				GameInstance->GetInventoryManager()->DeductItem(m_ItemQuickSlotsArray[1]);

				AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
				if (IsValid(GameModeBase))
				{
					//QuickSlot갯수변경
					UQuickItemSlotWidget* QuickItemSlotWidget = GameModeBase->GetMainHUDWidget()->GetQuickSlotWidget()->
					                                                          GetQuickItemSlotWidget(1);
					QuickItemSlotWidget->SlotRefresh(m_ItemQuickSlotsArray[1]->Count);

					//인벤토리 갯수변경
					UInventoryWidget* InventoryWidget = GameModeBase->GetMainHUDWidget()->GetMenuWidget()->
					                                                  GetInventoryWidget();
					InventoryWidget->DeductItemCount(m_ItemQuickSlotsArray[1]);
				}
			}
			else //아이템퀵슬롯이 비어잇을때
			{
				//PrintViewport(2.f, FColor::Yellow, TEXT("2번 슬롯이 비어있습니다"));
			}
		}
	}
}

void APlayerCharacter::ItemQuickSlot3Key()
{
	if (!m_IsWaitingRoom && !m_IsUIMode)
	{
		UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());

		if (IsValid(GameInstance))
		{
			if (m_ItemQuickSlotsArray[2])
			{
				GameInstance->GetInventoryManager()->DeductItem(m_ItemQuickSlotsArray[2]);

				AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
				if (IsValid(GameModeBase))
				{
					//QuickSlot갯수변경
					UQuickItemSlotWidget* QuickItemSlotWidget = GameModeBase->GetMainHUDWidget()->GetQuickSlotWidget()->
																			GetQuickItemSlotWidget(2);
					QuickItemSlotWidget->SlotRefresh(m_ItemQuickSlotsArray[2]->Count);

					//인벤토리 갯수변경
					UInventoryWidget* InventoryWidget = GameModeBase->GetMainHUDWidget()->GetMenuWidget()->
																	GetInventoryWidget();
					InventoryWidget->DeductItemCount(m_ItemQuickSlotsArray[2]);
				}
			}
			//else //아이템퀵슬롯이 비어잇을때
				//PrintViewport(2.f, FColor::Yellow, TEXT("3번 슬롯이 비어있습니다"));
				
		}
	}
}

void APlayerCharacter::ItemQuickSlot4Key()
{
	if (!m_IsWaitingRoom && !m_IsUIMode)
	{
		UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());

		if (IsValid(GameInstance))
		{
			if (m_ItemQuickSlotsArray[3])
			{
				GameInstance->GetInventoryManager()->DeductItem(m_ItemQuickSlotsArray[3]);

				AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
				if (IsValid(GameModeBase))
				{
					//QuickSlot갯수변경
					UQuickItemSlotWidget* QuickItemSlotWidget = GameModeBase->GetMainHUDWidget()->GetQuickSlotWidget()->
																			GetQuickItemSlotWidget(3);
					QuickItemSlotWidget->SlotRefresh(m_ItemQuickSlotsArray[3]->Count);

					//인벤토리 갯수변경
					UInventoryWidget* InventoryWidget = GameModeBase->GetMainHUDWidget()->GetMenuWidget()->
																	GetInventoryWidget();
					InventoryWidget->DeductItemCount(m_ItemQuickSlotsArray[3]);
				}
			}
			//else //아이템퀵슬롯이 비어잇을때
				//PrintViewport(2.f, FColor::Yellow, TEXT("4번 슬롯이 비어있습니다"));
		}
	}
}

void APlayerCharacter::ItemQuickSlot5Key()
{
	if (!m_IsWaitingRoom && !m_IsUIMode)
	{
		UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());

		if (IsValid(GameInstance))
		{
			if (m_ItemQuickSlotsArray[4])
			{
				GameInstance->GetInventoryManager()->DeductItem(m_ItemQuickSlotsArray[4]);

				AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
				if (IsValid(GameModeBase))
				{
					//QuickSlot갯수변경
					UQuickItemSlotWidget* QuickItemSlotWidget = GameModeBase->GetMainHUDWidget()->GetQuickSlotWidget()->
					                                                          GetQuickItemSlotWidget(4);
					QuickItemSlotWidget->SlotRefresh(m_ItemQuickSlotsArray[4]->Count);

					//인벤토리 갯수변경
					UInventoryWidget* InventoryWidget = GameModeBase->GetMainHUDWidget()->GetMenuWidget()->
					                                                  GetInventoryWidget();
					InventoryWidget->DeductItemCount(m_ItemQuickSlotsArray[4]);
				}
			}
			else //아이템퀵슬롯이 비어잇을때
			{
				//PrintViewport(2.f, FColor::Yellow, TEXT("5번 슬롯이 비어있습니다"));
			}
		}
	}
}

void APlayerCharacter::Attack()
{
}

void APlayerCharacter::SPRecovery()
{
	if (m_PlayerInfo.SP < m_PlayerInfo.SPMax)
	{
		//기력회복은 초당 전체 기력의 1/100
		m_PlayerInfo.SP += (m_PlayerInfo.SPMax * 0.01f);

		if (m_PlayerInfo.SP > m_PlayerInfo.SPMax)
			m_PlayerInfo.SP = m_PlayerInfo.SPMax;

		//UMG 기력 변경
		AProject1GameModeBase* gameMode = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (IsValid(gameMode))
		{
			UMainHUDWidget* mainHUDWidget = gameMode->GetMainHUDWidget();

			if (IsValid(mainHUDWidget))
			{
				UPlayerHUDWidget* playerHUDWidget = mainHUDWidget->GetPlayerHUDWidget();

				if (IsValid(playerHUDWidget))
				{
					playerHUDWidget->SetSPPercent(m_PlayerInfo.SP / (float)m_PlayerInfo.SPMax);
					playerHUDWidget->SetSPText(FString::Printf(TEXT("%d / %d"), m_PlayerInfo.SP, m_PlayerInfo.SPMax));
				}
			}
		}
	}
}

void APlayerCharacter::GhostTrailOn()
{
	GetWorldTimerManager().SetTimer(m_GhostTrailTimerHandle, this, &APlayerCharacter::GhostTrailFunc, m_GhostTrailTime, true);
}
void APlayerCharacter::GhostTrailOff()
{
	GetWorldTimerManager().ClearTimer(m_GhostTrailTimerHandle);
}
void APlayerCharacter::GhostTrailFunc()
{
	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AGhostCharacter* GhostCharacter = GetWorld()->SpawnActor<AGhostCharacter>(AGhostCharacter::StaticClass(),
		GetMesh()->GetComponentLocation(), GetMesh()->GetComponentRotation(),param);
	GhostCharacter->SetMesh(m_Mesh);
	GhostCharacter->CopyAnimation(GetMesh());
}

void APlayerCharacter::SetUI()
{
	AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameModeBase)
	{
		UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();
		if (MainHUDWidget)
		{
			UPlayerHUDWidget* PlayerHUDWidget = MainHUDWidget->GetPlayerHUDWidget();
			if (PlayerHUDWidget)
			{
				PlayerHUDWidget->SetCharacterImage(m_PlayerInfo.CharacterTexture);
				PlayerHUDWidget->SetHPPercent(m_PlayerInfo.HP / (float)m_PlayerInfo.HPMax);
				PlayerHUDWidget->SetSPPercent(m_PlayerInfo.SP / (float)m_PlayerInfo.SPMax);
				PlayerHUDWidget->SetEXPPercent(m_PlayerInfo.EXP / (float)m_PlayerInfo.EXPMax);
				PlayerHUDWidget->SetHPText(FString::Printf(TEXT("%d / %d"), m_PlayerInfo.HP, m_PlayerInfo.HPMax));
				PlayerHUDWidget->SetSPText(FString::Printf(TEXT("%d / %d"), m_PlayerInfo.SP, m_PlayerInfo.SPMax));
				PlayerHUDWidget->SetLevelText(FString::FromInt(m_PlayerInfo.Level));
				PlayerHUDWidget->SetEXPText(FString::Printf(TEXT("%d / %d"), m_PlayerInfo.EXP, m_PlayerInfo.EXPMax));
			}

			UMenuWidget* MenuWidget = MainHUDWidget->GetMenuWidget();
			if (MenuWidget)
			{
				MenuWidget->GetMenuCommonWidget()->GetStatsWidget()->SetDatas(m_PlayerInfo);
			}
		}
	}
}


void APlayerCharacter::AttackEnd()
{
	m_AttackEnable = true;
}

void APlayerCharacter::DashEnd()
{
	m_AttackEnable = true;
	m_TrailParticle->SetVisibility(false);
	GhostTrailOff();
}



void APlayerCharacter::DetectMonster()
{
	TArray<FHitResult> resultArray;
	FVector loc = GetActorLocation();
	FCollisionQueryParams param(NAME_None, false, this);
	bool collision = GetWorld()->SweepMultiByChannel(resultArray, loc, loc,
	                                                 FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel9,
	                                                 FCollisionShape::MakeSphere(3000.f), param);
	if (collision)
	{
		AProject1GameModeBase* gameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (gameModeBase)
		{
			gameModeBase->GetMainHUDWidget()->GetMinimapWidget()->ClearMonsterImageArray();
		}
		for (auto& ele : resultArray)
		{
			FVector relativeLoc = ele.GetActor()->GetActorLocation() - loc;

			if (gameModeBase)
			{
				gameModeBase->GetMainHUDWidget()->GetMinimapWidget()->AddMonster(relativeLoc);
			}
		}
	}
}


void APlayerCharacter::DetectRoom()
{
	TArray<FHitResult> resultArray;
	FVector loc = GetActorLocation();
	FCollisionQueryParams param(NAME_None, false, this);
	bool collision = GetWorld()->SweepMultiByChannel(resultArray, loc, loc,
	                                                 FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel11,
	                                                 FCollisionShape::MakeSphere(1500.f), param);
	if (collision)
	{
		AProject1GameModeBase* gameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (gameModeBase)
		{
			gameModeBase->GetMainHUDWidget()->GetMinimapWidget()->ClearRoomImageArray();
		}
		for (auto& ele : resultArray)
		{
			FVector relativeLoc = ele.GetActor()->GetActorLocation() - loc;

			if (gameModeBase)
			{
				ARoom* Room = Cast<ARoom>(ele.GetActor());
				if (Room)
					gameModeBase->GetMainHUDWidget()->GetMinimapWidget()->AddRoom(relativeLoc, Room);
			}
		}
	}
}

void APlayerCharacter::DetectDoor()
{
	TArray<FHitResult> resultArray;
	FVector loc = GetActorLocation();
	FCollisionQueryParams param(NAME_None, false, this);
	bool collision = GetWorld()->SweepMultiByChannel(resultArray, loc, loc,
	                                                 FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel13,
	                                                 FCollisionShape::MakeSphere(3000.f), param);
	if (collision)
	{
		AProject1GameModeBase* gameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if (gameModeBase)
		{
			UMinimapWidget* MinimapWidget = gameModeBase->GetMainHUDWidget()->GetMinimapWidget();
			MinimapWidget->ClearDoorImageArray();
		}
		for (auto& ele : resultArray)
		{
			FVector relativeLoc = ele.GetActor()->GetActorLocation() - loc;

			if (gameModeBase)
			{
				gameModeBase->GetMainHUDWidget()->GetMinimapWidget()->AddDoor(relativeLoc);
			}
		}
	}
}
