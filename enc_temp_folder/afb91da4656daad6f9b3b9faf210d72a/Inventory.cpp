// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "DA_Item.h"
#include "WBP_InventorySlot.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

int UInventory::GetNumItems()
{
	return ItemRefArray.Num();
}

void UInventory::AddItem(UDA_Item* ItemToAdd, int NumToAdd)
{
	// Try to find the index of the item in the inventory
	int IndexOfItem = ItemRefArray.Find(ItemToAdd);

	// If the item is already in the inventory, add to the count of that item
	if (IndexOfItem != INDEX_NONE)
	{
		ItemCountArray[IndexOfItem] += NumToAdd;
	}
	// otherwise add a new item slot to the inventory
	else
	{
		ItemRefArray.Add(ItemToAdd);
		ItemCountArray.Add(NumToAdd);
	}
}

void UInventory::RemoveItem(UDA_Item* ItemToRemove, int AmountToRemove)
{
	// Find item in inventory
	int IndexOfItemToRemove = ItemRefArray.Find(ItemToRemove);

	// Check if the item actually exists in the inventory
	if (IndexOfItemToRemove != INDEX_NONE)
	{
		// If we're removing less than the total count of the item, just subtract the amount
		if (AmountToRemove < ItemCountArray[IndexOfItemToRemove])
		{
			ItemCountArray[IndexOfItemToRemove] -= AmountToRemove;
		}
		// Otherwise remove whole item from the inventory
		else
		{
			ItemRefArray.RemoveAt(IndexOfItemToRemove);
			ItemCountArray.RemoveAt(IndexOfItemToRemove);
		}
	}
}


