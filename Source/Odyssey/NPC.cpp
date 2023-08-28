// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "DlgSystem/DlgManager.h"
#include "OdysseyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UIManager.h"
#include "Highlighter.h"
#include "DialogueComponent.h"
#include "Utility.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();

	UIManager = Utility::GetUIManager(this);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("ANPC::BeginPlay: Invalid UIManager"));
		return;
	}

	DialogueComponent = FindComponentByClass<UDialogueComponent>();
	if (!IsValid(DialogueComponent)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("ANPC::BeginPlay: Invalid DialogueComponent"), *GetName()); 
		return;
	}

	GetInputPromptWidgetComponent();
	CheckIfIsInteractable();
}

void ANPC::GetInputPromptWidgetComponent()
{
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (!IsValid(InputPromptActorComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("ANPC::GetInputPromptWidgetComponent: Invalid InputPromptActorComponent on %s"), *GetName());
		return;
	}
	
	InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
}

FName ANPC::GetParticipantName_Implementation() const
{
	if (!IsValid(DialogueComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("ANPC::GetParticipantName_Implementation: Invalid DialogueComponent on %s"), *GetName());
		return FName();
	}
	
	return DialogueComponent->GetParticipantName();
}

FText ANPC::GetParticipantDisplayName_Implementation(FName ActiveSpeaker) const
{
	if (!IsValid(DialogueComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("ANPC::GetParticipantDisplayName_Implementation: Invalid DialogueComponent on %s"), *GetName());
		return FText();
	}

	return DialogueComponent->GetParticipantDisplayName(ActiveSpeaker);
}

void ANPC::SetIsInteractable(bool NewInteractable)
{
	IsInteractable = NewInteractable;
}

bool ANPC::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

void ANPC::Highlight_Implementation(bool IsHighlighted)
{
	UHighlighter* HighlighterComponent = FindComponentByClass<UHighlighter>();
	if (!IsValid(HighlighterComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("ANPC::Highlight_Implementation: Invalid HighlighterComponent on %s"), *GetName());
		return;
	}

	HighlighterComponent->SetHighlight(IsHighlighted);
}

void ANPC::DisplayInputPrompt_Implementation(bool IsVisible)
{
	if (!IsValid(InputPromptWidgetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("No input prompt widget found on %s in NPC, DisplayInputPrompt"), *GetName());
		return;
	}

	InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
}

void ANPC::CheckIfIsInteractable()
{
	if (IsValid(DialogueComponent))
	{
		// Check if there are any dialogues in the dialogue component, it's interactable
		int NumDialogues = DialogueComponent->GetNumDialogues();
		if (NumDialogues > 0)
		{
			SetIsInteractable(true);
		}
		else
		{
			SetIsInteractable(false);
		}
	}
	else 
	{
		// If the NPC doesn't have a dialogue component, they're not interactable
		SetIsInteractable(false);
	}
}
