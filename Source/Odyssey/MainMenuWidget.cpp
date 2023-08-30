// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "UIManager.h"
#include "Kismet/GameplayStatics.h"
#include "Utility.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIManager = Utility::GetUIManager(this);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::NativeConstruct: Invalid UIManager"));
		return;
	}
}

void UMainMenuWidget::HandleContinueGameButtonClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleContinueGameBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayHUDWidgetOnly();
}

void UMainMenuWidget::HandleNewGameButtonClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleNewGameBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->OverlayNewGameAlertWidget();
}

void UMainMenuWidget::HandleOptionsButtonClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleOptionsBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayOptionsMenuWidget();
}

void UMainMenuWidget::HandleQuitGameButtonClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleQuitGameBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->OverlayQuitGameAlertWidget();
}

void UMainMenuWidget::HandleCreditsButtonClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleCreditsBtnClicked: Invalid UIManager"));
		return;
	}
	//UIManager->DisplayCreditsWidget();
}
