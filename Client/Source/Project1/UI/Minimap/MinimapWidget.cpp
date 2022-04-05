// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "../MainHUDWidget.h"
#include "Blueprint/WidgetTree.h"
#include "../../Map/Room.h"
#include "Project1/Trigger/RoomTrigger.h"

void UMinimapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_PlayerArrowImage = Cast<UImage>(GetWidgetFromName(TEXT("PlayerImage")));
	m_PlayerCanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("PlayerCanvasPanel")));
	m_MonsterCanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("MonsterCanvasPanel")));
	m_RoomCanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("RoomCanvasPanel")));
	m_DoorCanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("DoorCanvasPanel")));
	
	//몬스터이미지 오브젝트풀
	for (int32 i = 0; i < 30; i++)
	{
		FString name = FString::Printf(TEXT("Monster%d"), i);
		UImage* image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *name);
		image->SetVisibility(ESlateVisibility::Collapsed);
		image->SetBrushTintColor(FSlateColor(FLinearColor(1.f,0.f,0.f,1.f)));
		
		UCanvasPanelSlot* canvasPanelSlot = m_MonsterCanvasPanel->AddChildToCanvas(image);
		canvasPanelSlot->SetSize(FVector2D(10.f, 10.f));
		canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		
		m_MonsterImageArray.Add(image);
	}
	m_MonsterImageNum = 0;

	//룸이미지 오브젝트풀
	for (int32 i = 0; i < 20; i++)
	{
		FString name = FString::Printf(TEXT("Room%d"), i);
		UImage* image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *name);
		image->SetVisibility(ESlateVisibility::Collapsed);
		
		UTexture2D* Texture = LoadObject<UTexture2D>(GetWorld(), TEXT("Texture2D'/Game/01Resources/UI/Minimap/Image/Room.Room'"));
		image->SetBrushFromTexture(Texture);
		image->SetBrushSize(FVector2D(300.f,300.f));
		
		UCanvasPanelSlot* canvasPanelSlot = m_RoomCanvasPanel->AddChildToCanvas(image);
		canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		
		m_RoomImageArray.Add(image);
	}
	m_RoomImageNum = 0;
	
	//도어이미지 오브젝트풀
	for (int32 i = 0; i < 50; i++)
	{
		FString name = FString::Printf(TEXT("Door%d"), i);
		UImage* image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *name);
		image->SetVisibility(ESlateVisibility::Collapsed);
		
		UTexture2D* Texture = LoadObject<UTexture2D>(GetWorld(), TEXT("Texture2D'/Game/01Resources/UI/Minimap/Image/Door.Door'"));
		image->SetBrushFromTexture(Texture);
		image->SetBrushSize(FVector2D(700.f,700.f));
		
		UCanvasPanelSlot* canvasPanelSlot = m_DoorCanvasPanel->AddChildToCanvas(image);
		canvasPanelSlot->SetSize(FVector2D(15.f, 15.f));
		canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		
		m_DoorImageArray.Add(image);
	}
	m_DoorImageNum = 0;
}

void UMinimapWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	
}

void UMinimapWidget::RotateMinimap(float Yaw)
{
	m_PlayerCanvasPanel->SetRenderTransformAngle(Yaw);
}

void UMinimapWidget::AddMonster(const FVector& Loc)
{
	FVector2D ImageLoc;
	//언리얼 씬 상에서 X,Y좌표에서 UMG에서의 X,Y좌표로 변경.
	ImageLoc.X = Loc.Y;
	ImageLoc.Y = Loc.X * -1.f;
	//배율 (나눗셈은 연산이 곱셈보다 많이 먹으니 곱셈으로 사용)
	ImageLoc *= 0.05f;
	//원점에서 좌표 이동.
	ImageLoc.X += 150.f;
	ImageLoc.Y += 150.f;
	
	//풀 크기를 초과할시, 풀 크기 늘려줌.
	if(m_MonsterImageNum == m_MonsterImageArray.Num())
	{
		FString name = FString::Printf(TEXT("Monster%d"), m_MonsterImageNum);
		UImage* image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *name);
		
		image->SetVisibility(ESlateVisibility::Collapsed);
		image->SetBrushTintColor(FSlateColor(FLinearColor(1.f,0.f,0.f,1.f)));
	
		UCanvasPanelSlot* canvasPanelSlot = m_MonsterCanvasPanel->AddChildToCanvas(image);
		canvasPanelSlot->SetSize(FVector2D(10.f, 10.f));
		canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	
		m_MonsterImageArray.Add(image);
		
	}
	m_MonsterImageArray[m_MonsterImageNum]->SetVisibility(ESlateVisibility::Visible);
	UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(m_MonsterImageArray[m_MonsterImageNum]->Slot);
	canvasPanelSlot->SetPosition(ImageLoc);
	
	m_MonsterImageNum++;
}


void UMinimapWidget::ClearMonsterImageArray()
{
	for(int32 i = 0; i<m_MonsterImageNum; i++)
	{
		m_MonsterImageArray[i]->SetVisibility(ESlateVisibility::Collapsed);
	}
	m_MonsterImageNum = 0;
}


void UMinimapWidget::AddRoom(const FVector& Loc, ARoom* Room)
{
	FVector2D ImageLoc;
	//언리얼 씬 상에서 X,Y좌표에서 UMG에서의 X,Y좌표로 변경.
	ImageLoc.X = Loc.Y;
	ImageLoc.Y = Loc.X * -1.f;
	//배율 (나눗셈은 연산이 곱셈보다 많이 먹으니 곱셈으로 사용)
	ImageLoc *= 0.05f;
	//원점에서 좌표 이동.
	ImageLoc.X += 150.f;
	ImageLoc.Y += 150.f;
	
	//풀 크기를 초과할시, 풀 크기 늘려줌.
	if(m_RoomImageNum == m_RoomImageArray.Num())
	{
		FString name = FString::Printf(TEXT("Room%d"), m_RoomImageNum);
		UImage* image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *name);
		
		image->SetVisibility(ESlateVisibility::Collapsed);
		UTexture2D* Texture = LoadObject<UTexture2D>(GetWorld(), TEXT("Texture2D'/Game/01Resources/UI/Minimap/Image/Room.Room'"));
		image->SetBrushFromTexture(Texture);
		image->SetBrushSize(FVector2D(300.f,300.f));
		
		UCanvasPanelSlot* canvasPanelSlot = m_RoomCanvasPanel->AddChildToCanvas(image);
		canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		
		m_RoomImageArray.Add(image);
		
	}
	m_RoomImageArray[m_RoomImageNum]->SetVisibility(ESlateVisibility::Visible);
	UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(m_RoomImageArray[m_RoomImageNum]->Slot);
	canvasPanelSlot->SetPosition(ImageLoc);
	FVector BoxExtent = Room->GetBoxExtent();
	canvasPanelSlot->SetSize(FVector2D(BoxExtent.Y * 0.1f, BoxExtent.X * 0.1f));
	
	m_RoomImageNum++;
}

void UMinimapWidget::ClearRoomImageArray()
{
	for(int32 i = 0; i<m_RoomImageNum; i++)
	{
		m_RoomImageArray[i]->SetVisibility(ESlateVisibility::Collapsed);
	}
	m_RoomImageNum = 0;
}

void UMinimapWidget::AddDoor(const FVector& Loc)
{
	FVector2D ImageLoc;
	//언리얼 씬 상에서 X,Y좌표에서 UMG에서의 X,Y좌표로 변경.
	ImageLoc.X = Loc.Y;
	ImageLoc.Y = Loc.X * -1.f;
	//배율 (나눗셈은 연산이 곱셈보다 많이 먹으니 곱셈으로 사용)
	ImageLoc *= 0.05f;
	//원점에서 좌표 이동.
	ImageLoc.X += 150.f;
	ImageLoc.Y += 150.f;
	
	//풀 크기를 초과할시, 풀 크기 늘려줌.
	if(m_DoorImageNum == m_DoorImageArray.Num())
	{
		FString name = FString::Printf(TEXT("Door%d"), m_DoorImageNum);
		UImage* image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *name);
		
		image->SetVisibility(ESlateVisibility::Collapsed);
		UTexture2D* Texture = LoadObject<UTexture2D>(GetWorld(), TEXT("Texture2D'/Game/01Resources/UI/Minimap/Image/Door.Door'"));
		image->SetBrushFromTexture(Texture);
		image->SetBrushSize(FVector2D(700.f,700.f));
		UCanvasPanelSlot* canvasPanelSlot = m_DoorCanvasPanel->AddChildToCanvas(image);
		canvasPanelSlot->SetSize(FVector2D(15.f, 15.f));
		canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	
		m_DoorImageArray.Add(image);
		
	}
	m_DoorImageArray[m_DoorImageNum]->SetVisibility(ESlateVisibility::Visible);
	UCanvasPanelSlot* canvasPanelSlot = Cast<UCanvasPanelSlot>(m_DoorImageArray[m_DoorImageNum]->Slot);
	canvasPanelSlot->SetPosition(ImageLoc);
	
	m_DoorImageNum++;
}

void UMinimapWidget::ClearDoorImageArray()
{
	for(int32 i = 0; i<m_DoorImageNum; i++)
	{
		m_DoorImageArray[i]->SetVisibility(ESlateVisibility::Collapsed);
	}
	m_DoorImageNum = 0;
}


//
// void UMinimapWidget::SetRoomImage(ARoom* Room)
// {
// 	FString name = FString::Printf(TEXT("RoomImage%d"), m_RoomArray.Num()-1);
// 	UImage* image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *name);
// 	
// 	//룸 텍스처 변경
// 	UTexture2D* Texture = LoadObject<UTexture2D>(GetWorld(), TEXT("Texture2D'/Game/01Resources/UI/Minimap/Image/Room.Room'"));
// 	image->SetBrushFromTexture(Texture);
//
// 	//이미지 세부 설정
// 	UCanvasPanelSlot* canvasPanelSlot = m_RoomCanvasPanel->AddChildToCanvas(image);
// 	
// 	canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
// 	
// 	FVector2D RoomSize = Room->GetRoomTrigger()->GetTriggerSize();
// 	canvasPanelSlot->SetSize(FVector2D(RoomSize.X * 0.1f, RoomSize.Y * 0.1f));
// 	
// 	//UI상의 좌표로 변경.
// 	canvasPanelSlot->SetPosition(FVector2D(0.f,0.f));
// }