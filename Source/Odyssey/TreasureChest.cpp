// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureChest.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "Highlighter.h"


ATreasureChest::ATreasureChest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATreasureChest::BeginPlay()
{
	Super::BeginPlay();

	GetInputPromptWidgetComponent();
}

void ATreasureChest::GetInputPromptWidgetComponent()
{
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (!IsValid(InputPromptActorComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("ATreasureChest::GetInputPromptWidgetComponent: Invalid InputPromptActorComponent on %s"), *GetName());
		return;
	}

	InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
	if (!IsValid(InputPromptWidgetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("ATreasureChest::GetInputPromptWidgetComponent: Invalid InputPromptWidgetComponent on %s"), *GetName());
		return;
	}
}

void ATreasureChest::Highlight_Implementation(bool IsHighlighted)
{
	UHighlighter* HighlighterComponent = FindComponentByClass<UHighlighter>();
	if (!IsValid(HighlighterComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("ATreasureChest::Highlight_Implementation: Invalid HighlighterComponent on %s"), *GetName());
		return;
	}

	HighlighterComponent->SetHighlight(IsHighlighted);
}

void ATreasureChest::DisplayInputPrompt_Implementation(bool IsVisible)
{
	if (!IsValid(InputPromptWidgetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("ATreasureChest::DisplayInputPrompt_Implementation: Invalid InputPromptWidgetComponent"));
		return;
	}
	InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
}

bool ATreasureChest::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

