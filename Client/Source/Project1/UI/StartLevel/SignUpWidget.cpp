// Fill out your copyright notice in the Description page of Project Settings.


#include "SignUpWidget.h"

#include "Project1/Project1GameInstance.h"
#include <string>

#include "Project1/Global/ClientBlueprintFunctionLibrary.h"
#include "Project1/Global/Message/ClientToServer.h"


void USignUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_SignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("SignUpButton")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_SignUpButton->OnClicked.AddDynamic(this, &USignUpWidget::SignUpButtonClicked);
	m_CloseButton->OnClicked.AddDynamic(this, &USignUpWidget::CloseButtonClicked);

	m_IDTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IDTextBox")));
	m_PWTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PWTextBox")));
	m_IDTextBox->OnTextChanged.AddDynamic(this, &USignUpWidget::IDTextBoxChanged);
	m_PWTextBox->OnTextChanged.AddDynamic(this, &USignUpWidget::PWTextBoxChanged);

	m_IDString = "";
	m_PWString = "";
}

void USignUpWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void USignUpWidget::SignUpButtonClicked()
{
	//서버로 회원가입 패킷 보내기.
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());

	if(GameInst->GetIsClientMode())
	{
		return;		
	}
	
	std::string ID;
	std::string PW;
	UClientBlueprintFunctionLibrary::FStringToUTF8(m_IDString, ID);
	UClientBlueprintFunctionLibrary::FStringToUTF8(m_PWString, PW);

	SignUpMessage Message;
	Message.m_ID = ID;
	Message.m_PW = PW;
	
	GameServerSerializer Serializer;
	Message.Serialize(Serializer);
	
	if (!GameInst->Send(Serializer.GetData()))
	{
		PrintViewport(2.f, FColor::Red, TEXT("SignUp Message Send Error!"));
	}
}

void USignUpWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void USignUpWidget::IDTextBoxChanged(const FText& Text)
{
	m_IDString = Text.ToString();
}

void USignUpWidget::PWTextBoxChanged(const FText& Text)
{
	m_PWString = Text.ToString();
}