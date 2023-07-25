// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "DA_Item.h"



// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


/*
 * Tries to add an item to the inventory as long as there's available space.
 * If the item is stackable and already in the inventory then add to the quantity,
 * otherwise add a new item slot to the inventory.
 * 
 * @param Item - The item to add to the inventory
 * @return bool - Whether or not the item was added to the inventory
 */
bool UInventory::AddToInventory(UDA_Item* ItemToAdd, int ItemCount)
{
	// If the item doesn't exist in the inventory then add it
	if (!ItemRefArray.Contains(ItemToAdd))
	{
		ItemRefArray.Add(ItemToAdd);
		UE_LOG(LogTemp, Display, TEXT("New item added to inventory in Inventory, AddToInventory"));
	}
	// Otherwise find it and add to its count
	else
	{
		for (int idx = 0; idx < ItemRefArray.Num(); idx++)
		{
			if (ItemRefArray[idx] == ItemToAdd)
			{
				ItemCountArray[idx] += ItemCount;
			}
		}
		UE_LOG(LogTemp, Display, TEXT("Item count increased in Inventory, AddToInventory"));
	}

	OnInventoryUpdated.Broadcast();

	return false;
}

void UInventory::RemoveFromInventory(UDA_Item* ItemToRemove)
{

}

int UInventory::GetMaxInventorySize()
{
	return MaxInventorySize;
}

int UInventory::GetNumItems()
{
	return ItemRefArray.Num();
}


