// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "OdysseyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DlgSystem/DlgManager.h"
#include "UIManager.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get world in DialogueComponent, BeginPlay"));
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get player pawn in DialogueComponent, BeginPlay"));
		return;
	}

	AOdysseyCharacter* PlayerCharacter = Cast<AOdysseyCharacter>(PlayerPawn);
	if (!IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get player character in DialogueComponent, BeginPlay"));
		return;
	}
		
	UIManager = PlayerCharacter->FindComponentByClass<UUIManager>();
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get UIManager in DialogueComponent, BeginPlay"));
		return;
	}
}

void UDialogueComponent::PopulateDialogueBodyText()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot get UIManager in DialogueComponent, PopulateDialogueBodyText"));
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
		UE_LOG(LogTemp, Error, TEXT("Cannot get UIManager in DialogueComponent, PopulateDialogueOptionsText"));
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
		UE_LOG(LogTemp, Error, TEXT("Cannot get UIManager in DialogueComponent, StartDialogue"));
		return false;
	}
	if (!IsValid(Dialogue))
	{
		UE_LOG(LogTemp, Error, TEXT("Dialogue is null in DialogueComponent, StartDialogue"));
		return false;
	}
	if (DlgParticipants.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("DlgParticipants has no participants in DialogueComponent, StartDialogue"));
		return false;
	}
	if (!IsValid(DialogueParticipantAvatar))
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueParticipantAvatar is null in DialogueComponent, StartDialogue"));
		return false;
	}
	if (DialogueParticipantDisplayName.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueParticipantDisplayName is empty or whitespace in DialogueComponent, StartDialogue"));
		return false;
	}

	DialogueContext = UDlgManager::StartDialogue(Dialogue, DlgParticipants);
	if (!IsValid(DialogueContext))
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null in DialogueComponent, StartDialogue"));
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
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null in DialogueComponent, GetDialogueBodyText"));
		return FText();
	}

	const FText Text = DialogueContext->GetActiveNodeText();
	return Text;
}

TArray<FText> UDialogueComponent::GetDialogueOptionsText()
{
	if (!IsValid(DialogueContext))
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null in DialogueComponent, GetDialogueOptionsText"));
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
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null in DialogueComponent, SelectDialogueOption"));
		return false;
	}
	
	if (!DialogueContext->IsValidOptionIndex(Index))
	{
		UE_LOG(LogTemp, Error, TEXT("Index is invalid in DialogueComponent, SelectDialogueOption"));
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