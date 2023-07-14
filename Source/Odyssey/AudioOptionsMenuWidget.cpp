// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioOptionsMenuWidget.h"
#include "Components/Button.h"
#include "UIManager.h"

void UAudioOptionsMenuWidget::NativeConstruct()
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

void UAudioOptionsMenuWidget::HandleBackBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Quit game button clicked"));

	UIManager->DisplayOptionsMenuWidget();
}
