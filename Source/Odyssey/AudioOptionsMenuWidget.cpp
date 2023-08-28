// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioOptionsMenuWidget.h"
#include "Components/Button.h"
#include "UIManager.h"
#include "Utility.h"

void UAudioOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIManager = Utility::GetUIManager(this);
}

void UAudioOptionsMenuWidget::HandleBackBtnClicked()
{
	if (!IsValid(UIManager)) { 
		UE_LOG(LogTemp, Error, TEXT("UAudioOptionsMenuWidget::HandleBackBtnClicked: invalid UIManager")); 
		return; 
	}

	UIManager->DisplayOptionsMenuWidget();
}
