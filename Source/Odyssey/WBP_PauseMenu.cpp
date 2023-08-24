// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_PauseMenu.h"
#include "UIManager.h"

void UWBP_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Get player pawn
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		// Get UI Manager component
		UIManager = Cast<UUIManager>(PlayerPawn->GetComponentByClass(UUIManager::StaticClass()));

		if (!UIManager) { UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in MainMenuWidget, NativeConstruct")); }
	}
}


void UWBP_PauseMenu::HandleContinueGameBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Continue game button clicked"));
	UIManager->DisplayHUDWidgetOnly();

}

void UWBP_PauseMenu::HandleOptionsBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Options button clicked"));
	UIManager->DisplayOptionsMenuWidget();
}

void UWBP_PauseMenu::HandleMainMenuBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("New game button clicked"));
	UIManager->DisplayMainMenuWidget();

}

void UWBP_PauseMenu::HandleQuitGameBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Quit game button clicked"));
	UIManager->OverlayQuitGameAlertWidget();

}

