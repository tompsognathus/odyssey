// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "UIManager.h"
#include "Kismet/GameplayStatics.h"


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
	UIManager->OverlayNewGameAlertWidget();

}

void UMainMenuWidget::HandleOptionsBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Options button clicked"));
	UIManager->DisplayOptionsMenuWidget();
}

void UMainMenuWidget::HandleQuitGameBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Quit game button clicked"));
	UIManager->OverlayQuitGameAlertWidget();
}
