 // Fill out your copyright notice in the Description page of Project Settings.


#include "RPEncounterWidget.h"
#include "UIManager.h"
#include "Components/TextBlock.h"

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
	UIManager->SelectDialogueOption(0, DialogueOwner);
}

void URPEncounterWidget::HandleOption2BtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 2 button clicked"));
	UIManager->SelectDialogueOption(1, DialogueOwner);
}

void URPEncounterWidget::HandleOption3BtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 3 button clicked"));
	UIManager->SelectDialogueOption(2, DialogueOwner);
}

void URPEncounterWidget::HandleOption4BtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Option 4 button clicked"));
	UIManager->SelectDialogueOption(3, DialogueOwner);
}

void URPEncounterWidget::SetBodyText(FText NewAdventureText)
{
	if (AdventureText)
	{
		AdventureText->SetText(NewAdventureText);
	} else { UE_LOG(LogTemp, Error, TEXT("AdventureText not found in RPEncounterWidget, SetBodyText")); }
}

void URPEncounterWidget::SetOptionText(int OptionNumber, FText NewOptionText)
{
	switch (OptionNumber)
	{
	case 1:
		if (OptionText1)
		{
			OptionText1->SetText(NewOptionText);
		}
		break;
	case 2:
		if (OptionText2)
		{
			OptionText2->SetText(NewOptionText);
		}
		break;
	case 3:
		if (OptionText3)
		{
			OptionText3->SetText(NewOptionText);
		}
		break;
	case 4:
		if (OptionText4)
		{
			OptionText4->SetText(NewOptionText);
		}
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid Option Number"))
			break;
	}
}

UHUDWidget* URPEncounterWidget::GetHUDWidget()
{
	return HUDWidget;
}
