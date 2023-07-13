// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_OptionsMenu.h"

#include "UIManager.h"


void UWBP_OptionsMenu::NativeConstruct()
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

void UWBP_OptionsMenu::HandleAudioBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Audio button clicked"));

}

void UWBP_OptionsMenu::HandleVideoBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Video button clicked"));

}

void UWBP_OptionsMenu::HandleGameplayBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Options button clicked"));
}

void UWBP_OptionsMenu::HandleBackBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Quit game button clicked"));

	UIManager->DisplayPreviousWidget();
}
