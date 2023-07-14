 // Fill out your copyright notice in the Description page of Project Settings.


#include "RPEncounterWidget.h"
#include "UIManager.h"

void URPEncounterWidget::NativeConstruct()
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

void URPEncounterWidget::HandleOption1BtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 1 button clicked"));

}

void URPEncounterWidget::HandleOption2BtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 2 button clicked"));

}

void URPEncounterWidget::HandleOption3BtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 3 button clicked"));

}

void URPEncounterWidget::HandleOption4BtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 4 button clicked"));

}
