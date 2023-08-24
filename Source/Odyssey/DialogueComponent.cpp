// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "OdysseyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DlgSystem/DlgManager.h"
#include "UIManager.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get UI Manager reference through posessed pawn
	AOdysseyCharacter* PlayerCharacter = Cast<AOdysseyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter)
	{
		UIManager = PlayerCharacter->FindComponentByClass<UUIManager>();
	
	} else { UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found")); }

}

void UDialogueComponent::PopulateDialogueBodyText()
{
	if (UIManager)
	{
		UIManager->SetRPEncounterBodyText(GetDialogueBodyText());
	
	} else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}

void UDialogueComponent::PopulateDialogueOptionsText()
{
	if (UIManager)
	{
		TArray<FText> Options = GetDialogueOptionsText();

		for (int i = 0; i < 4; i++)
		{
			if (i < Options.Num())
			{
				UIManager->SetRPEncounterOptionText(i + 1, Options[i]); // Options are currently indexed from 1
			}
			else
			{
				UIManager->SetRPEncounterOptionText(i + 1, FText::FromString(""));
			}
		}
	} else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}

bool UDialogueComponent::StartDialogue(UDlgDialogue* Dialogue, const TArray<UObject*>& DlgParticipants)
{
	DialogueContext = UDlgManager::StartDialogue(Dialogue, DlgParticipants);

	if (UIManager)
	{
		UIManager->DisplayRPEncounterWidget(this);
		PopulateDialogueBodyText();
		PopulateDialogueOptionsText();
		if (DialogueParticipantAvatar != nullptr)
		{
			UIManager->SetRPEncounterAvatar(DialogueParticipantAvatar);
	
		} else UE_LOG(LogTemp, Warning, TEXT("DialogueParticipantAvatar is null for %s - see DialogueComponent, StartDialogue."), *DialogueParticipantName.ToString());
	} else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }

	return DialogueContext != nullptr;
}

FText UDialogueComponent::GetDialogueBodyText()
{
	if (!DialogueContext)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null"));
		return FText();
	}

	const FText Text = DialogueContext->GetActiveNodeText();

	return Text;
}

TArray<FText> UDialogueComponent::GetDialogueOptionsText()
{
	TArray<FText> Options;
	if (!DialogueContext)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null"));
		return Options;
	}

	int OptionsNum = DialogueContext->GetOptionsNum();

	for (int i = 0; i < OptionsNum; i++)
	{
		Options.Add(DialogueContext->GetOptionText(i));
	}

	return Options;
}

bool UDialogueComponent::SelectDialogueOption(int32 Index)
{
	if (!DialogueContext || !DialogueContext->IsValidOptionIndex(Index))
	{
		return false;
	}

	if (!DialogueContext->ChooseOption(Index) || DialogueContext->HasDialogueEnded())
	{
		// Dialogue Has Ended
		DialogueContext = nullptr;
		return false;
	}

	return true;
}