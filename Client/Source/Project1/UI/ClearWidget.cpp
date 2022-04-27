#include "ClearWidget.h"


void UClearWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_RetryButton = Cast<UButton>(GetWidgetFromName(TEXT("RetryButton")));
	m_WaitingRoomButton = Cast<UButton>(GetWidgetFromName(TEXT("WaitingRoomButton")));
	m_RetryButton->OnClicked.AddDynamic(this, &UClearWidget::RetryButtonClicked);
	m_WaitingRoomButton->OnClicked.AddDynamic(this, &UClearWidget::WaitingRoomButtonClicked);
}

void UClearWidget::RetryButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
}

void UClearWidget::WaitingRoomButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("WaitingRoom"));
}
