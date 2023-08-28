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

void UMainMenuWidget::HandleContinueGameBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleContinueGameBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayHUDWidgetOnly();
}

void UMainMenuWidget::HandleNewGameBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleNewGameBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->OverlayNewGameAlertWidget();
}

void UMainMenuWidget::HandleOptionsBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleOptionsBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayOptionsMenuWidget();
}

void UMainMenuWidget::HandleQuitGameBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UMainMenuWidget::HandleQuitGameBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->OverlayQuitGameAlertWidget();
}
