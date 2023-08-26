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
	for (UStaticMeshComponent* StaticMesh : StaticMeshesToOutline)
	{
		StaticMesh->SetRenderCustomDepth(IsHighlighted);
	}

	for (USkeletalMeshComponent* SkeletalMesh : SkeletalMeshesToOutline)
	{
		SkeletalMesh->SetRenderCustomDepth(IsHighlighted);
	}
}

void UHighlighter::GetMeshesToOutline()
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


