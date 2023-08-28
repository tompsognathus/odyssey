 // Fill out your copyright notice in the Description page of Project Settings.


#include "RPEncounterWidget.h"
#include "UIManager.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Utility.h"

void URPEncounterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIManager = Utility::GetUIManager(this);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::NativeConstruct: Invalid UIManager"));
		return;
	}
}

void URPEncounterWidget::HandleOption1BtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::HandleOption1BtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->SelectDialogueOption(0, DialogueOwner);
}

void URPEncounterWidget::HandleOption2BtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::HandleOption2BtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->SelectDialogueOption(1, DialogueOwner);
}

void URPEncounterWidget::HandleOption3BtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::HandleOption3BtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->SelectDialogueOption(2, DialogueOwner);
}

void URPEncounterWidget::HandleOption4BtnClicked()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::HandleOption4BtnClicked: Invalid UIManager"));
		return;
	}
	UIManager->SelectDialogueOption(3, DialogueOwner);
}

void URPEncounterWidget::SetBodyText(FText NewAdventureText)
{
	if (!IsValid(AdventureText))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetBodyText: Invalid AdventureText"));
		return;
	}
	AdventureText->SetText(NewAdventureText);
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
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionText: Invalid Option Number"))
			break;
	}
}

void URPEncounterWidget::SetAvatar(UMaterial* NewAvatarMaterial, FText NewAvatarName)
{
	SetAvatarImage(NewAvatarMaterial);
	SetAvatarName(NewAvatarName);
}

void URPEncounterWidget::SetAvatarName(FText& NewAvatarName)
{
	if (NewAvatarName.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetAvatarName: NewAvatarName is empty or whitespace. Did you set it in the editor?"))
		return;
	}
	AvatarName->SetText(NewAvatarName);
}

void URPEncounterWidget::SetAvatarImage(UMaterial* NewAvatarMaterial)
{
	if (!IsValid(AvatarImg))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetAvatar: Invalid AvatarImg. Did you set it in the editor?"))
		return;
	}
	AvatarImg->SetBrushFromMaterial(NewAvatarMaterial);
}

UHUDWidget* URPEncounterWidget::GetHUDWidget()
{
	return HUDWidget;
}
