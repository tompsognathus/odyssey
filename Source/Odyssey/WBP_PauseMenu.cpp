// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_PauseMenu.h"
#include "UIManager.h"
#include "Utility.h"

void UWBP_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	UIManager = Utility::GetUIManager(this);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_PauseMenu::NativeConstruct: Invalid UIManager"));
		return;
	}
}


void UWBP_PauseMenu::HandleContinueGameBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_PauseMenu::HandleContinueGameBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayHUDWidgetOnly();
}

void UWBP_PauseMenu::HandleOptionsBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_PauseMenu::HandleOptionsBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayOptionsMenuWidget();
}

void UWBP_PauseMenu::HandleMainMenuBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_PauseMenu::HandleMainMenuBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->DisplayMainMenuWidget();
}

void UWBP_PauseMenu::HandleQuitGameBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_PauseMenu::HandleQuitGameBtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->OverlayQuitGameAlertWidget();
}

