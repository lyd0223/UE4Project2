#pragma once

#include "../GameInfo.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "WidgetDragDropOperation.generated.h"

UCLASS()
class PROJECT1_API UWidgetDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

protected:
	UUserWidget* m_Widget;
	FVector2D m_MousePos;

	public:
	UUserWidget* GetWidget() const
	{
		return m_Widget;
	}
	void SetWidget(UUserWidget* _Widget)
	{
		m_Widget = _Widget;
	}
	void SetMousePosition(const FVector2D& _MousePos)
	{
		m_MousePos = _MousePos;
	}
};
