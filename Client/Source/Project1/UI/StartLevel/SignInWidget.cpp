// Fill out your copyright notice in the Description page of Project Settings.


#include "SignInWidget.h"

#include "Project1/Project1GameInstance.h"
#include <string>

#include "Project1/Global/ClientBlueprintFunctionLibrary.h"
#include "Project1/Global/Message/ClientToServer.h"


void USignInWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_SignInButton = Cast<UButton>(GetWidgetFromName(TEXT("SignInButton")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_SignInButton->OnClicked.AddDynamic(this, &USignInWidget::SignInButtonClicked);
	m_CloseButton->OnClicked.AddDynamic(this, &USignInWidget::CloseButtonClicked);

	m_IDTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IDTextBox")));
	m_PWTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PWTextBox")));
	m_IDTextBox->OnTextChanged.AddDynamic(this, &USignInWidget::IDTextBoxChanged);
	m_PWTextBox->OnTextChanged.AddDynamic(this, &USignInWidget::PWTextBoxChanged);

	m_IDString = "";
	m_PWString = "";
}

void USignInWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void USignInWidget::SignInButtonClicked()
{
	//서버로 로그인 패킷 보내기.
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());

	if(GameInst->GetIsClientMode())
	{
		return;		
	}
	
	std::string ID;
	std::string PW;
	UClientBlueprintFunctionLibrary::FStringToUTF8(m_IDString, ID);
	UClientBlueprintFunctionLibrary::FStringToUTF8(m_PWString, PW);

	SignInMessage Message;
	Message.m_ID = ID;
	Message.m_PW = PW;
	
	GameServerSerializer Serializer;
	Message.Serialize(Serializer);
	
	if (!GameInst->Send(Serializer.GetData()))
	{
		PrintViewport(2.f, FColor::Red, TEXT("SignInMessage Send Error!"));
	}
}

void USignInWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void USignInWidget::IDTextBoxChanged(const FText& Text)
{
	m_IDString = Text.ToString();
}

void USignInWidget::PWTextBoxChanged(const FText& Text)
{
	m_PWString = Text.ToString();
}