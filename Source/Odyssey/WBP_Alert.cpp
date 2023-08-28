// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_Alert.h"
#include "UIManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Utility.h"

void UWBP_Alert::NativeConstruct()
{
	Super::NativeConstruct();

	UIManager = Utility::GetUIManager(this);
}

/***** Quit Game Alerts *****/
void UWBP_Alert::HandleQuitGameYesBtnClicked()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid World in WBP_Alert, HandleQuitGameBtnYesClicked"));
		return;
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid FirstPlayerController in WBP_Alert, HandleQuitGameBtnYesClicked"));
		return;
	}

	UKismetSystemLibrary::QuitGame(World, FirstPlayerController, EQuitPreference::Quit, false);
}

void UWBP_Alert::HandleQuitGameNoBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid UIManager in WBP_Alert, HandleQuitGameBtnNoClicked"));
		return;
	}

	UIManager->HideAllAlerts();
}

/***** New Game Alerts *****/
void UWBP_Alert::HandleNewGameYesBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid UIManager in WBP_Alert, HandleNewGameBtnYesClicked"));
		return;
	}

	UIManager->HideAllAlerts();
	UIManager->StartPrologue();
}

void UWBP_Alert::HandleNewGameNoBtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid UIManager in WBP_Alert, HandleNewGameBtnNoClicked"));
		return;
	}

	UIManager->HideAllAlerts();
}



