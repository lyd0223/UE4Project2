// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "MinimapWidget.generated.h"

UCLASS()
class PROJECT1_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_PlayerArrowImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_PlayerCanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_MonsterCanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_RoomCanvasPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_DoorCanvasPanel;
	
	TArray<UImage*> m_MonsterImageArray;
	int32 m_MonsterImageNum;
	
	TArray<UImage*> m_RoomImageArray;
	int32 m_RoomImageNum;
	
	TArray<UImage*> m_DoorImageArray;
	int32 m_DoorImageNum;
	

protected:
	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void RotateMinimap(float Yaw);

	void AddMonster(const FVector& Loc);
	
	void ClearMonsterImageArray();

	void AddRoom(const FVector& Loc, class ARoom* Room);
	
	void ClearRoomImageArray();
	
	void AddDoor(const FVector& Loc);
	
	void ClearDoorImageArray();
	//void SetRoomImage(class ARoom* Room);
};
