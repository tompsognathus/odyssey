 // Fill out your copyright notice in the Description page of Project Settings.


#include "RPEncounterWidget.h"
#include "UIManager.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
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
	if (!IsValid(OptionText1))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionText: Invalid OptionText1"));
		return;
	}
	if (!IsValid(OptionText2))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionText: Invalid OptionText2"));
		return;
	}
	if (!IsValid(OptionText3))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionText: Invalid OptionText3"));
		return;
	}
	if (!IsValid(OptionText4))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionText: Invalid OptionText4"));
		return;
	}

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

void URPEncounterWidget::SetOptionVisibility(int OptionNumber, bool IsVisible)
{
	if (!IsValid(OptionBtn1))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionVisibility: Invalid OptionBtn1"));
		return;
	}
	if (!IsValid(OptionBtn2))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionVisibility: Invalid OptionBtn2"));
		return;
	}
	if (!IsValid(OptionBtn3))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionVisibility: Invalid OptionBtn3"));
		return;
	}
	if (!IsValid(OptionBtn4))
	{
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionVisibility: Invalid OptionBtn4"));
		return;
	}

	ESlateVisibility ButtonVisibility = IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

	switch (OptionNumber)
	{
	case 1:
		if (OptionBtn1)
		{
			OptionBtn1->SetVisibility(ButtonVisibility);
		}
		break;
	case 2:
		if (OptionBtn2)
		{
			OptionBtn2->SetVisibility(ButtonVisibility);
		}
		break;
	case 3:
		if (OptionBtn3)
		{
			OptionBtn3->SetVisibility(ButtonVisibility);
		}
		break;
	case 4:
		if (OptionBtn4)
		{
			OptionBtn4->SetVisibility(ButtonVisibility);
		}
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("URPEncounterWidget::SetOptionVisibility: Invalid Option Number"))
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
