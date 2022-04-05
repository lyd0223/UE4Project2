
#include "GameInfo.h"

DEFINE_LOG_CATEGORY(UEKR2);

void PrintViewport(float Time, const FColor& Color, const FString& Text)
{
	GEngine->AddOnScreenDebugMessage(-1, Time, Color, Text);
}
