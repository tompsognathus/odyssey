// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBox.h"

// Sets default values for this component's properties
ULootBox::ULootBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SpawnLootableItems();
}

void ULootBox::SpawnLootableItems()
{
	// Spawn lootable items
	for (int idx = 0; idx < LootableItems.Num(); idx++)
	{
		TSubclassOf<AActor> LootableItemActorClass = LootableItemsRefs[idx];
		if (LootableItemActorClass)
		{
			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(LootableItemActorClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
			if (SpawnedActor)
			{
				LootableItems.Add(SpawnedActor);
			} else UE_LOG(LogTemp, Warning, TEXT("Failed to spawn lootable item %d. See LootBox, SpawnLootableItems"), idx);
		} else UE_LOG(LogTemp, Warning, TEXT("Failed to get lootable item class. See LootBox, SpawnLootableItems"));
	};
}


// Called when the game starts
void ULootBox::BeginPlay()
{
	Super::BeginPlay();


	// log the number of lootable items
	UE_LOG(LogTemp, Warning, TEXT("Lootable items: %d"), LootableItems.Num());
}


// Called every frame
void ULootBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

