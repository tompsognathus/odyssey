// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/WidgetComponent.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACannon::BeginPlay()
{
	Super::BeginPlay();

	GetInputPromptWidgetComponent();
}

void ACannon::GetInputPromptWidgetComponent()
{
	// Find the input prompt widget reference
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (InputPromptActorComponent)
	{
		InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in Cannon, BeginPlay"), *GetName()); }
}

void ACannon::DisplayInputPrompt_Implementation(bool IsVisible)
{
	// Set input prompt visibility
	if (InputPromptWidgetComponent)
	{
		InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in Cannon, DisplayInputPrompt"), *GetName()); }

}

bool ACannon::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

void ACannon::SetIsInteractable(bool NewIsInteractable)
{
	IsInteractable = NewIsInteractable;
}

