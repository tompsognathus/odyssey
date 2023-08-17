// Fill out your copyright notice in the Description page of Project Settings.


#include "Highlighter.h"

// Sets default values for this component's properties
UHighlighter::UHighlighter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHighlighter::BeginPlay()
{
	Super::BeginPlay();

	GetMeshesToOutline();
}

void UHighlighter::SetHighlight(bool IsHighlighted)
{
	// Print number of static meshes
	UE_LOG(LogTemp, Warning, TEXT("Number of static meshes: %i"), StaticMeshesToOutline.Num());
	// Print number of skeletal meshes
	UE_LOG(LogTemp, Warning, TEXT("Number of skeletal meshes: %i"), SkeletalMeshesToOutline.Num());

	if (StaticMeshesToOutline.Num() == 0 && SkeletalMeshesToOutline.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No meshes to highlight in Highlighter, SetHighlight"));
		return;
	}

	for (UStaticMeshComponent* StaticMesh : StaticMeshesToOutline)
	{
		StaticMesh->SetRenderCustomDepth(IsHighlighted);
	}

	for (USkeletalMeshComponent* SkeletalMesh : SkeletalMeshesToOutline)
	{
		SkeletalMesh->SetRenderCustomDepth(IsHighlighted);
	}
}

void UHighlighter::GetMeshesToOutline_Implementation()
{
	// Get all static and skeletal meshes from parent actor
	AActor* ParentActor = GetOwner();

	for (UActorComponent* ActorComponent : ParentActor->GetComponents())
	{
		UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(ActorComponent);
		if (StaticMeshComponent)
		{
			StaticMeshesToOutline.Add(StaticMeshComponent);
		}

		USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(ActorComponent);
		if (SkeletalMeshComponent)
		{
			SkeletalMeshesToOutline.Add(SkeletalMeshComponent);
		}
	}
}


