
#pragma once

#include "Project1/GameInfo.h"
#include "Engine/SceneCapture2D.h"
#include "MenuSceneCapture2D.generated.h"

UCLASS()
class PROJECT1_API AMenuSceneCapture2D : public ASceneCapture2D
{
	GENERATED_BODY()

	public:
	AMenuSceneCapture2D();
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* m_BelicaMeshActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* m_RevenantMeshActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* m_WraithMeshActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* m_TwinBlastMeshActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_Distance;
	
	protected:
	virtual void BeginPlay() override;
};
