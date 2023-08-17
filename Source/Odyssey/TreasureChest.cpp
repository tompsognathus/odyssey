// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureChest.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "Highlighter.h"


// Sets default values
ATreasureChest::ATreasureChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATreasureChest::BeginPlay()
{
	Super::BeginPlay();

	GetInputPromptWidgetComponent();

}

void ATreasureChest::GetInputPromptWidgetComponent()
{
	// Find the input prompt widget reference
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (InputPromptActorComponent)
	{
		InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in TreasureChest, BeginPlay"), *GetName()); }
}

void ATreasureChest::Highlight_Implementation(bool IsHighlighted)
{
	// Get Highlighter component
	UHighlighter* Highlighter = FindComponentByClass<UHighlighter>();

	if (Highlighter)
	{
		Highlighter->SetHighlight(IsHighlighted);

	} else { UE_LOG(LogTemp, Warning, TEXT("No highlighter component found on %s in TreasureChest, Highlight"), *GetName()); }
}

void ATreasureChest::DisplayInputPrompt_Implementation(bool IsVisible)
{
	// Set input prompt visibility
	if (InputPromptWidgetComponent)
	{
		InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in TreasureChest, DisplayInputPrompt"), *GetName()); }
	
}

bool ATreasureChest::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

