// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "DlgSystem/DlgManager.h"
#include "OdysseyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UIManager.h"
#include "Highlighter.h"

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

	GetMeshesToOutline(StaticMeshesToOutline, SkeletalMeshesToOutline);

	GetInputPromptWidgetComponent();

	// Get UI Manager reference through posessed pawn
	AOdysseyCharacter* PlayerCharacter = Cast<AOdysseyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerCharacter)
	{
		UIManager = PlayerCharacter->FindComponentByClass<UUIManager>();
	}
	else { UE_LOG(LogTemp, Error, TEXT("PlayerCharacter not found")); }

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

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void ANPC::GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT)
{
	// Get all components
	TArray<UActorComponent*> Components;

	for (UActorComponent* Component : GetComponents())
	{
		// If the component is a static mesh component, add it to the static mesh array
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component))
		{
			StaticMeshesToOutlineOUT.Add(StaticMeshComponent);
		}
		// If the component is a skeletal mesh component, add it to the skeletal mesh array
		else if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component))
		{
			SkeletalMeshesToOutlineOUT.Add(SkeletalMeshComponent);
		}
	}
}

void ANPC::CheckIfIsInteractable()
{
	// If the NPC has no dialogues attachted to them, they're not interactable
	if (Dialogues.Num() == 0)
	{
		SetIsInteractable(false);
	}
}


void ANPC::PopulateDialogueBodyText()
{
	if (UIManager)
	{
		UIManager->SetRPEncounterBodyText(GetDialogueBodyText());
	}
	else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}

void ANPC::PopulateDialogueOptionsText()
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
	}
	else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }
}

bool ANPC::StartDialogue(UDlgDialogue* Dialogue, const TArray<UObject*>& DlgParticipants)
{
	DialogueContext = UDlgManager::StartDialogue(Dialogue, DlgParticipants);

	if (UIManager)
	{
		UIManager->DisplayRPEncounterWidget(this);
		PopulateDialogueBodyText();
		PopulateDialogueOptionsText();

	} else { UE_LOG(LogTemp, Error, TEXT("UIManager not found")); }

	return DialogueContext != nullptr;
}

FText ANPC::GetDialogueBodyText()
{
	if (!DialogueContext)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null"));
	}

	const FText Text = DialogueContext->GetActiveNodeText();

	return Text;
}

TArray<FText> ANPC::GetDialogueOptionsText()
{
	if (!DialogueContext)
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueContext is null"));
	}

	TArray<FText> Options;
	int OptionsNum = DialogueContext->GetOptionsNum();

	for (int i = 0; i < OptionsNum; i++)
	{
		Options.Add(DialogueContext->GetOptionText(i));
	}

	return Options;
}

bool ANPC::SelectDialogueOption(int32 Index)
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