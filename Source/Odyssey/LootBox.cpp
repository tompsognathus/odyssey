// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBox.h"

// Sets default values for this component's properties
ULootBox::ULootBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void ULootBox::BeginPlay()
{
	Super::BeginPlay();

	// Check if the item and count arrays have the same size as we need a count for each item
	if (LootableItemRefArray.Num() != LootableItemCountArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Item and ItemCount arrays are not the same size!"));
		return;		
	}
}


// Called every frame
void ULootBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULootBox::RemoveItem(UDA_Item* ItemToRemove, int AmountToRemove)
{
	// Find the index of the item to remove
	int ItemIndex = LootableItemRefArray.Find(ItemToRemove);

	// If the item is not in the array, return
	if (ItemIndex == INDEX_NONE)
	{
		UE_LOG(LogTemp, Error, TEXT("Item not found in LootableItemRefArray in LootBox, RemoveItem!"));
		return;
	}
	// If the amount to remove is greater than the amount in the array, warn and remove what's actually in the array
	else if (AmountToRemove > LootableItemCountArray[ItemIndex])
	{
		UE_LOG(LogTemp, Warning, TEXT("AmountToRemove is greater than the amount of items in the array, removing all items! See LootBox, RemovItem"));
		// Remove the item from the arrays
		LootableItemRefArray.RemoveAt(ItemIndex);
		LootableItemCountArray.RemoveAt(ItemIndex);
	}
	// If the amount to remove is equal to the amount in the array, remove the item from the array
	else if (AmountToRemove == LootableItemCountArray[ItemIndex])
	{
		// Remove the item from the arrays
		LootableItemRefArray.RemoveAt(ItemIndex);
		LootableItemCountArray.RemoveAt(ItemIndex);
	}
	// Otherwise decrease the counter for said item
	else
	{
		LootableItemCountArray[ItemIndex] -= AmountToRemove;
	}
}

