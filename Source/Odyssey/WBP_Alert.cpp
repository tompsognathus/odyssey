// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Alert.h"
#include "UIManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/GameplayStatics.h>


void UWBP_Alert::NativeConstruct()
{
	Super::NativeConstruct();

	// Get player pawn
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		// Get UI Manager component
		UIManager = Cast<UUIManager>(PlayerPawn->GetComponentByClass(UUIManager::StaticClass()));

		if (!UIManager) { UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in WBP_Alert, NativeConstruct")); }
	}
}

/***** Quit Game Alerts *****/
void UWBP_Alert::HandleQuitGameYesBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Yes button clicked on Quit Game alert in WBP_Alert, HandleQuitGameBtnYesClicked"));

	// Quit game
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UWBP_Alert::HandleQuitGameNoBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("No button clicked on Quit Game alert in WBP_Alert, HandleQuitGameBtnNoClicked"));
	UIManager->HideAllAlerts();
}

/***** New Game Alerts *****/
void UWBP_Alert::HandleNewGameYesBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Yes button clicked on New Game alert in WBP_Alert, HandleNewGameBtnYesClicked"));

	UIManager->HideAllAlerts();
	// Play Prologue
	UIManager->StartPrologue();

}

void UWBP_Alert::HandleNewGameNoBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("No button clicked on New Game alert in WBP_Alert, HandleNewGameBtnNoClicked"));
	UIManager->HideAllAlerts();
}



