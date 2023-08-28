// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include "Components/WidgetComponent.h"

ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();

	GetInputPromptWidgetComponent();
}

void ATeleporter::GetInputPromptWidgetComponent()
{
	UActorComponent* InputPromptActorComponent = GetComponentByClass(UWidgetComponent::StaticClass());
	if (!IsValid(InputPromptActorComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("ATeleporter::GetInputPromptWidgetComponent: Invalid InputPromptActorComponent on %s"), GetName());
		return;
	}
	InputPromptWidgetComponent = Cast<UWidgetComponent>(InputPromptActorComponent);
}

void ATeleporter::DisplayInputPrompt_Implementation(bool IsVisible)
{
	if (!IsValid(InputPromptWidgetComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("ATeleporter::DisplayInputPrompt: Invalid InputPromptWidgetComponent on %s"), GetName());
		return;
	}
	InputPromptWidgetComponent->SetHiddenInGame(!IsVisible);
}

bool ATeleporter::GetIsInteractable_Implementation()
{
	return IsInteractable;
}

void ATeleporter::SetIsInteractable(bool NewIsInteractable)
{
	IsInteractable = NewIsInteractable;
}