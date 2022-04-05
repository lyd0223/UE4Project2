// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalEffect.h"

#include "../AssetManager/AssetPathLoader.h"

// Sets default values
ANormalEffect::ANormalEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	SetRootComponent(m_ParticleSystem);

	m_AssetLoop = false;

	m_LifeTime = 0.f;
	m_LifeTimeACC = 0.f;

	m_SoundVolume = 1.f;
}

// Called when the game starts or when spawned
void ANormalEffect::BeginPlay()
{
	Super::BeginPlay();

	

	// OnSystemFinished : 이 파티클시스템컴포넌트가 가지고 있는 파티클시스템이 재생이
	// 모두 종료가 되었을 경우 호출될 함수를 지정해둔다.
	// 종료시 지정된 함수가 호출된다.
	if (!m_AssetLoop)
		m_ParticleSystem->OnSystemFinished.AddDynamic(this, &ANormalEffect::ParticleFinish);
}

// Called every frame
void ANormalEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_LifeTime != 0.f)
	{
		m_LifeTimeACC += DeltaTime;

		if(m_LifeTimeACC >= m_LifeTime)
		{
			Destroy();
		}
	}
	
}

void ANormalEffect::LoadParticle(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(GetWorld(), *Path);

	if (Particle)
		m_ParticleSystem->SetTemplate(Particle);
}

void ANormalEffect::LoadParticleAsync(const FString& Name)
{
	UAssetPathLoader* AssetPath = UAssetPathLoader::StaticClass()->GetDefaultObject<UAssetPathLoader>();

	const FSoftObjectPath* Path = AssetPath->FindParticlePath(Name);

	if (!Path)
		return;

	m_AsyncParticlePath = *Path;

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();

	m_AsyncParticleLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncParticlePath,
		FStreamableDelegate::CreateUObject(this, &ANormalEffect::LoadParticleAsyncComplete));
}

void ANormalEffect::LoadParticleAsyncComplete()
{
	m_AsyncParticleLoadHandle->ReleaseHandle();

	TAssetPtr<UParticleSystem>	NewParticle(m_AsyncParticlePath);

	if (NewParticle)
	{
		m_ParticleSystem->SetTemplate(NewParticle.Get());
		//m_ParticleSystem->OnSystemFinished.AddDynamic(this, &ANormalEffect::ParticleFinish);
	}
}

void ANormalEffect::LoadSound(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	if(Sound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());
}

void ANormalEffect::LoadSoundAsync(const FString& Name)
{
	UAssetPathLoader* AssetPath = UAssetPathLoader::StaticClass()->GetDefaultObject<UAssetPathLoader>();

	const FSoftObjectPath* Path = AssetPath->FindSoundPath(Name);

	if (!Path)
		return;

	m_AsyncSoundPath = *Path;

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();

	m_AsyncSoundLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncSoundPath,
		FStreamableDelegate::CreateUObject(this, &ANormalEffect::LoadSoundAsyncComplete));
}

void ANormalEffect::LoadSoundAsyncComplete()
{
	m_AsyncSoundLoadHandle->ReleaseHandle();

	TAssetPtr<USoundBase>	NewSound(m_AsyncSoundPath);

	if (NewSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), NewSound.Get(), GetActorLocation(), m_SoundVolume);
}

void ANormalEffect::ParticleFinish(UParticleSystemComponent* Particle)
{
	Destroy();

	// m_ParticleSystem;
	//
	// m_AsyncParticlePath;
	// m_AsyncSoundPath;
	//
	// m_AsyncParticleLoadHandle;
	// m_AsyncSoundLoadHandle;
	//
	// m_SoundVolume;
	//
	// m_AssetLoop;
	//
	// m_LifeTimeACC;
	// m_LifeTime;
}

void ANormalEffect::SetEffectScale(FVector Scale)
{
	SetActorScale3D(Scale);
}