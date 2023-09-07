// Fill out your copyright notice in the Description page of Project Settings.


#include "Highlighter.h"

// Sets default values for this component's properties
UHighlighter::UHighlighter()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UHighlighter::BeginPlay()
{
	Super::BeginPlay();

	GetMeshesToOutline();
}

void UHighlighter::SetHighlight(bool IsHighlighted)
{
	if (StaticMeshesToOutline.Num() == 0 && SkeletalMeshesToOutline.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UHighlighter::SetHighlight: No meshes to outline on %s"), *GetOwner()->GetName());
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

void UHighlighter::GetMeshesToOutline()
{
	AActor* ParentActor = GetOwner();
	if (!IsValid(ParentActor))
	{
		UE_LOG(LogTemp, Error, TEXT("UHighlighter::GetMeshesToOutline: Invalid ParentActor"));
		return;
	}

	for (UActorComponent* ActorComponent : ParentActor->GetComponents())
	{
		UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(ActorComponent);
		if (StaticMeshComponent)
		{
			// Skip the mesh if it is not tagged with the outline tag and we want to only outline tagged meshes
			if (bOutlineOnlyTaggedMeshes)
			{
				if (!StaticMeshComponent->ComponentHasTag(OutlineMeshTag))
				{
					continue;
				}
			}

			StaticMeshesToOutline.Add(StaticMeshComponent);
		}

		USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(ActorComponent);
		if (SkeletalMeshComponent)
		{
			// Skip the mesh if it is not tagged with the outline tag and we want to only outline tagged meshes
			if (bOutlineOnlyTaggedMeshes)
			{
				if (!SkeletalMeshComponent->ComponentHasTag(OutlineMeshTag))
				{
					continue;
				}
			}

			SkeletalMeshesToOutline.Add(SkeletalMeshComponent);
		}
	}

}


