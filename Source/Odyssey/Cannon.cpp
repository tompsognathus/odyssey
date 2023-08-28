// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/WidgetComponent.h"

ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACannon::BeginPlay()
{
	Super::BeginPlay();

	GetInputPromptWidgetComponent();
}

void ACannon::GetInputPromptWidgetComponent()
{
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (!IsValid(InputPromptActorComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("ACannon::GetInputPromptWidgetComponent: No input prompt actor component found on %s"), *GetName());
		return;
	}

	InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
	if (!IsValid(InputPromptWidgetComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("ACannon::GetInputPromptWidgetComponent: No input prompt widget found on %s"), *GetName());
	}
}

void ACannon::DisplayInputPrompt_Implementation(bool IsVisible)
{
	if (!IsValid(InputPromptWidgetComponent)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("ACannon::DisplayInputPrompt_Implementation: No input prompt widget found on %s"), *GetName());
		return;
	}

	InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
}

bool ACannon::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

void ACannon::SetIsInteractable(bool NewIsInteractable)
{
	IsInteractable = NewIsInteractable;
}

