// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Alert.h"
#include "UIManager.h"
#include "Kismet/KismetSystemLibrary.h"

void UWBP_Alert::NativeConstruct()
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

void UWBP_Alert::HandleQuitGameYesBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Yes button clicked"));

	// Quit game
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UWBP_Alert::HandleQuitGameNoBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("No button clicked"));
	UIManager->HideAllAlerts();
}

void UWBP_Alert::HandleNewGameYesBtnClicked()
{
}

void UWBP_Alert::HandleNewGameNoBtnClicked()
{
}



