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

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("World not found in NPC, BeginPlay"));
		return;
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("FirstPlayerController not found in NPC, BeginPlay"));
		return;
	}

	APawn* PlayerPawn = FirstPlayerController->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerPawn not found in NPC, BeginPlay"));
		return;
	}

	AOdysseyCharacter* PlayerCharacter = Cast<AOdysseyCharacter>(PlayerPawn);
	if (!IsValid(PlayerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found in NPC, BeginPlay"));
		return;
	}

	UActorComponent* UIManagerComponent = PlayerPawn->GetComponentByClass(UUIManager::StaticClass());
	if (!IsValid(UIManagerComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManagerComponent in ANPC, BeginPlay"));
		return;
	}

	UIManager = Cast<UUIManager>(UIManagerComponent);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot cast UIManagerComponent to UIManager in ANPC, BeginPlay"));
		return;
	}

	DialogueComponent = FindComponentByClass<UDialogueComponent>();
	if (!IsValid(DialogueComponent)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No dialogue component found on %s in NPC, BeginPlay"), *GetName()); 
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
		UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in NPC, GetInputPromptWidgetComponent"), *GetName());
		return;
	}
	
	InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
}

FName ANPC::GetParticipantName_Implementation() const
{
	if (!IsValid(DialogueComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("No dialogue component found on %s in NPC, GetParticipantName_Implementation"), *GetName());
		return FName();
	}
	
	return DialogueComponent->GetParticipantName();
}

FText ANPC::GetParticipantDisplayName_Implementation(FName ActiveSpeaker) const
{
	if (!IsValid(DialogueComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("No dialogue component found on %s in NPC, GetParticipantDisplayName_Implementation"), *GetName());
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
	UHighlighter* Highlighter = FindComponentByClass<UHighlighter>();
	if (!IsValid(Highlighter))
	{
		UE_LOG(LogTemp, Error, TEXT("Highlighter not found in NPC, Highlight_Implementation"));
		return;
	}

	Highlighter->SetHighlight(IsHighlighted);
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
