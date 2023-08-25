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
		UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in Cannon, BeginPlay"), *GetName());
		return;
	}

	InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
}

void ACannon::DisplayInputPrompt_Implementation(bool IsVisible)
{
	if (!IsValid(InputPromptWidgetComponent)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in Cannon, DisplayInputPrompt"), *GetName());
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

