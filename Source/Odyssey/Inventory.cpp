// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "DA_Item.h"
#include "WBP_InventorySlot.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;

}

int UInventory::GetNumItems()
{
	return ItemRefArray.Num();
}

void UInventory::AddItem(UDA_Item* ItemToAdd, int NumToAdd)
{
	if (!IsValid(ItemToAdd))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventory::AddItem: Invalid ItemToAdd"));
		return;
	}

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
	if (!IsValid(ItemToRemove))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventory::RemoveItem: Invalid ItemToRemove"));
		return;
	}

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


