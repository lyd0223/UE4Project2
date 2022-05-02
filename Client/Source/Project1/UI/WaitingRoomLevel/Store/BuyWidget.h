#pragma once

#include "../../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "BuyWidget.generated.h"

UCLASS()
class PROJECT1_API UBuyWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_CountAdditionButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_CountSubtractionButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_CountText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_PriceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_BuyButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_CloseButton;

	FItem* m_Item;
	int m_Count;
	int m_Price;
protected:
	virtual void NativeConstruct() override;

public:
	void OpenBuyWidget(FItem* Item);
	
	UFUNCTION()
	void CountAdditionButtonClicked();
	UFUNCTION()
	void CountSubtractionButtonClicked();
	
	UFUNCTION()
	void BuyButtonClicked();
	
	UFUNCTION()
	void CloseButtonClicked();
};
