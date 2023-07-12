// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "UIManager.h"


void UMainMenuWidget::NativeConstruct()
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

void UMainMenuWidget::HandleContinueGameBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Continue game button clicked"));
	UIManager->DisplayHUDWidgetOnly();

}

void UMainMenuWidget::HandleNewGameBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("New game button clicked"));
	UIManager->DisplayHUDWidgetOnly();

}

void UMainMenuWidget::HandleOptionsBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Options button clicked"));
}

void UMainMenuWidget::HandleQuitGameBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Quit game button clicked"));

	UIManager->OverlayQuitGameAlertWidget();
	// Quit game
	//UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
