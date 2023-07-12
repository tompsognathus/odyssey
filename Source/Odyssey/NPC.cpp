// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	GetMeshesToOutline(StaticMeshesToOutline, SkeletalMeshesToOutline);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::SetIsInteractable(bool NewInteractable)
{
	IsInteractable = NewInteractable;
}

void ANPC::Highlight_Implementation(bool IsHighlighted)
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

void ANPC::GetMeshesToOutline(TArray<UStaticMeshComponent*>& StaticMeshesToOutlineOUT, TArray<USkeletalMeshComponent*>& SkeletalMeshesToOutlineOUT)
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

