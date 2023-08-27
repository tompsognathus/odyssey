// Fill out your copyright notice in the Description page of Project Settings.


#include "LooseFloorboard.h"
#include "Highlighter.h"
#include "Components/WidgetComponent.h"

ALooseFloorboard::ALooseFloorboard()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ALooseFloorboard::BeginPlay()
{
	Super::BeginPlay();

	GetInputPromptWidgetComponent();

	// I think the following is unnecessary because it's now done by the highlighter component, but keeping it here for now just in case. TODO: Remove if not needed.
	//GetMeshesToOutline(StaticMeshesToOutline, SkeletalMeshesToOutline);
}

void ALooseFloorboard::GetInputPromptWidgetComponent()
{
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (!IsValid(InputPromptActorComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in LooseFloorboard, BeginPlay"), *GetName());
		return;
	}

	InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
}

void ALooseFloorboard::Highlight_Implementation(bool IsHighlighted)
{
	UHighlighter* Highlighter = FindComponentByClass<UHighlighter>();
	if (!IsValid(Highlighter))
	{
		UE_LOG(LogTemp, Warning, TEXT("No highlighter found on %s in LooseFloorboard, Highlight"), *GetName());
		return;
	}

	Highlighter->SetHighlight(IsHighlighted);
}

void ALooseFloorboard::DisplayInputPrompt_Implementation(bool IsVisible)
{
	if (!IsValid(InputPromptWidgetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("No input prompt widget found on %s in LooseFloorboard, DisplayInputPrompt"), *GetName());
		return;
	}

	InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
}

bool ALooseFloorboard::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

void ALooseFloorboard::SetIsInteractable(bool NewIsInteractable)
{
	IsInteractable = NewIsInteractable;
}


// I think the following is unnecessary because it's now done by the highlighter component, but keeping it here for now just in case. TODO: Remove if not needed.
//void ALooseFloorboard::GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT)
//{
//	// Get all components
//	TArray<UActorComponent*> Components;
//
//	for (UActorComponent* Component : GetComponents())
//	{
//		// If the component is a static mesh component, add it to the static mesh array
//		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component))
//		{
//			StaticMeshesToOutlineOUT.Add(StaticMeshComponent);
//		}
//		// If the component is a skeletal mesh component, add it to the skeletal mesh array
//		else if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(Component))
//		{
//			SkeletalMeshesToOutlineOUT.Add(SkeletalMeshComponent);
//		}
//	}
//}
