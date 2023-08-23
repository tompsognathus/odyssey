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

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	GetInputPromptWidgetComponent();

	// Get UI Manager reference through posessed pawn
	AOdysseyCharacter* PlayerCharacter = Cast<AOdysseyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter)
	{
		UIManager = PlayerCharacter->FindComponentByClass<UUIManager>();
	}
	else { UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found")); }

	// Get reference to dialogue component
	DialogueComponent = FindComponentByClass<UDialogueComponent>();
	if (!DialogueComponent) { UE_LOG(LogTemp, Warning, TEXT("No dialogue component found on %s in NPC, BeginPlay"), *GetName()); }

	CheckIfIsInteractable();
}

void ANPC::GetInputPromptWidgetComponent()
{
	// Find the input prompt widget reference
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (InputPromptActorComponent)
	{
		InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in TreasureChest, BeginPlay"), *GetName()); }
}

FName ANPC::GetParticipantName_Implementation() const
{
	if (DialogueComponent)
	{
		return DialogueComponent->GetParticipantName();

	} else { UE_LOG(LogTemp, Warning, TEXT("No dialogue component found on %s in NPC, GetParticipantName"), *GetName()); }

	return FName();
}

FText ANPC::GetParticipantDisplayName_Implementation(FName ActiveSpeaker) const
{
	if (DialogueComponent)
	{
		return DialogueComponent->GetParticipantDisplayName(ActiveSpeaker);

	} else { UE_LOG(LogTemp, Warning, TEXT("No dialogue component found on %s in NPC, GetParticipantDisplayName"), *GetName()); }
	return FText();
}

//UMaterial* ANPC::GetParticipantIcon_Implementation(FName ActiveSpeaker, FName ActiveSpeakerState) const
//{
//	if (DialogueComponent)
//	{
//		return DialogueComponent->GetParticipantAvatar(ActiveSpeaker, ActiveSpeakerState);
//
//	} else { UE_LOG(LogTemp, Warning, TEXT("No dialogue component found on %s in NPC, GetParticipantIcon"), *GetName()); }
//	return nullptr;
//}


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
	// Get reference to Highlighter
	UHighlighter* Highlighter = FindComponentByClass<UHighlighter>();

	if (Highlighter)
	{
		Highlighter->SetHighlight(IsHighlighted);
	} else { UE_LOG(LogTemp, Warning, TEXT("No highlighter found on %s in NPC, Highlight"), *GetName()); }

}

void ANPC::DisplayInputPrompt_Implementation(bool IsVisible)
{
	// Set input prompt visibility
	if (InputPromptWidgetComponent)
	{
		InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in NPC, DisplayInputPrompt"), *GetName()); }

}

void ANPC::CheckIfIsInteractable()
{
	if (DialogueComponent)
	{
		// Check if there are any dialogues in the dialogue component
		int NumDialogues = DialogueComponent->GetNumDialogues();

		// If there are any dialogues, the NPC is interactable
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
