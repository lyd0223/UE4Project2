#include "CharacterNicknameWidget.h"


void UCharacterNicknameWidget::NativeConstruct()
{
	m_NicknameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NicknameText")));

	if(m_SetNicknameDeligate.IsBound())
		m_SetNicknameDeligate.Execute();
}
