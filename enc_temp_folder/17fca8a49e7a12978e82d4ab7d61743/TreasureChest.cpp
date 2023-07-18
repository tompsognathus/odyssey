// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureChest.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"


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

	GetMeshesToOutline(StaticMeshesToOutline, SkeletalMeshesToOutline);

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
	//Set render custom depth to true for each static and skeletal mesh
	for (UStaticMeshComponent* StaticMesh : StaticMeshesToOutline)
	{
		StaticMesh->SetRenderCustomDepth(IsHighlighted);
	}
	for (USkeletalMeshComponent* SkeletalMesh : SkeletalMeshesToOutline)
	{
		SkeletalMesh->SetRenderCustomDepth(IsHighlighted);
	}
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

TArray<UObject*> ATreasureChest::Loot_Implementation()
{
	return TArray<UObject*>(); // Return empty array
}

void ATreasureChest::GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT)
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