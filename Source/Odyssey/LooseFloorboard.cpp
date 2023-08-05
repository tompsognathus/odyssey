// Fill out your copyright notice in the Description page of Project Settings.


#include "LooseFloorboard.h"
#include "Highlighter.h"
#include "Components/WidgetComponent.h"

// Sets default values
ALooseFloorboard::ALooseFloorboard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALooseFloorboard::BeginPlay()
{
	Super::BeginPlay();
	
	GetInputPromptWidgetComponent();
}

void ALooseFloorboard::GetInputPromptWidgetComponent()
{
	// Find the input prompt widget reference
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (InputPromptActorComponent)
	{
		InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
	
	} else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in Cannon, BeginPlay"), *GetName()); }
}

void ALooseFloorboard::Highlight_Implementation(bool IsHighlighted)
{
	// Get Highlighter component
	UHighlighter* Highlighter = FindComponentByClass<UHighlighter>();

	if (Highlighter)
	{
	UE_LOG(LogTemp, Warning, TEXT("Highlight_Implementation"));
		Highlighter->SetHighlight(IsHighlighted);

	} else { UE_LOG(LogTemp, Warning, TEXT("No highlighter component found on %s in TreasureChest, Highlight"), *GetName()); }
}

void ALooseFloorboard::DisplayInputPrompt_Implementation(bool IsVisible)
{
	// Set input prompt visibility
	if (InputPromptWidgetComponent)
	{
		InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);

	} else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in TreasureChest, DisplayInputPrompt"), *GetName()); }

}

bool ALooseFloorboard::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

void ALooseFloorboard::SetIsInteractable(bool NewIsInteractable)
{
	IsInteractable = NewIsInteractable;
}
