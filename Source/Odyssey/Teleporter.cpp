// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();

	GetInputPromptWidgetComponent();
}

void ATeleporter::GetInputPromptWidgetComponent()
{
	// Find the input prompt widget reference
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (InputPromptActorComponent)
	{
		InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in Teleporter, BeginPlay"), *GetName()); }
}

void ATeleporter::DisplayInputPrompt_Implementation(bool IsVisible)
{
	// Set input prompt visibility
	if (InputPromptWidgetComponent)
	{
		InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("No input prompt widget found on %s in Teleporter, DisplayInputPrompt"), *GetName()); }

}

bool ATeleporter::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

void ATeleporter::SetIsInteractable(bool NewIsInteractable)
{
	IsInteractable = NewIsInteractable;
}