// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "OdysseyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DlgSystem/DlgManager.h"
#include "UIManager.h"
#include "Utility.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	UIManager = Utility::GetUIManager(this);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::BeginPlay: Invalid UIManager"));
		return;
	}
}

void UDialogueComponent::PopulateDialogueBodyText()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::PopulateDialogueBodyText: Invalid UIManager"));
		return;
	}

	FText DialogueBodyText = GetDialogueBodyText();
	if (DialogueBodyText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueBodyText is empty or whitespace in DialogueComponent, PopulateDialogueBodyText"));
		return;
	}

	UIManager->SetRPEncounterBodyText(DialogueBodyText);
}

void UDialogueComponent::PopulateDialogueOptionsText()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::PopulateDialogueOptionsText: Invalid UIManager"));
		return;
	}

	TArray<FText> Options = GetDialogueOptionsText();

	for (int i = 0; i < 4; i++) // Currently only 4 options are supported
	{
		if (i < Options.Num())
		{
			UIManager->SetRPEncounterOptionText(i + 1, Options[i]); // Options are currently indexed from 1
		}
		else
		{
			// TODO: Hide/disable the option button and also hide the A/B/C/D text
			UIManager->SetRPEncounterOptionText(i + 1, FText::FromString(""));
		}
	}
}

bool UDialogueComponent::StartDialogue(UDlgDialogue* Dialogue, const TArray<UObject*>& DlgParticipants)
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::StartDialogue: Invalid UIManager"));
		return false;
	}
	if (!IsValid(Dialogue))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::StartDialogue: Invalid Dialogue"));
		return false;
	}
	if (DlgParticipants.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::StartDialogue: DlgParticipants has no participants on %s"), *GetName());
		return false;
	}
	if (!IsValid(DialogueParticipantAvatar))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::StartDialogue: Invalid DialogueParticipantAvatar"));
		return false;
	}
	if (DialogueParticipantDisplayName.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::StartDialogue: DialogueParticipantDisplayName is empty or whitespace on %s"), *GetName());
		return false;
	}

	DialogueContext = UDlgManager::StartDialogue(Dialogue, DlgParticipants);
	if (!IsValid(DialogueContext))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::StartDialogue: Invalid DialogueContext"));
		return false;
	}

	UIManager->DisplayRPEncounterWidget(this);
	PopulateDialogueBodyText();
	PopulateDialogueOptionsText();
	UIManager->SetRPEncounterAvatar(DialogueParticipantAvatar, DialogueParticipantDisplayName);

	return DialogueContext != nullptr;
}

FText UDialogueComponent::GetDialogueBodyText()
{
	if (!IsValid(DialogueContext))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::GetDialogueBodyText: Invalid DialogueContext"));
		return FText();
	}

	const FText Text = DialogueContext->GetActiveNodeText();
	return Text;
}

TArray<FText> UDialogueComponent::GetDialogueOptionsText()
{
	if (!IsValid(DialogueContext))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::GetDialogueOptionsText: Invalid DialogueContext"));
		return TArray<FText>();
	}

	TArray<FText> Options;

	int OptionsNum = DialogueContext->GetOptionsNum();

	for (int i = 0; i < OptionsNum; i++)
	{
		Options.Add(DialogueContext->GetOptionText(i));
	}

	return Options;
}

bool UDialogueComponent::SelectDialogueOption(int32 Index)
{
	if (!IsValid(DialogueContext))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::SelectDialogueOption: Invalid DialogueContext"));
		return false;
	}
	
	if (!DialogueContext->IsValidOptionIndex(Index))
	{
		UE_LOG(LogTemp, Error, TEXT("UDialogueComponent::SelectDialogueOption: Invalid option index"));
		return false;
	}

	bool DidChooseOption = DialogueContext->ChooseOption(Index);
	if (!DidChooseOption || DialogueContext->HasDialogueEnded())
	{
		// Dialogue Has Ended
		DialogueContext = nullptr;
		return false;
	}

	return true;
}