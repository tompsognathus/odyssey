// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBox.h"
#include "WBP_InventorySlot.h"

ULootBox::ULootBox()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts
void ULootBox::BeginPlay()
{
	Super::BeginPlay();

	// We need to make sure each item also has a corresponding count, so we make sure the arrays are the same size
	if (ItemRefArray.Num() != ItemCountArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Item and ItemCount arrays are not the same size!"));
		return;		
	}
}

void ULootBox::RemoveItem(UDA_Item* ItemToRemove, int AmountToRemove)
{
	// Try to find the index of the item in the loot box
	int IndexOfItem = ItemRefArray.Find(ItemToRemove);

	// Check if the item actually exists in the loot box
	if (IndexOfItem != INDEX_NONE)
	{
		// If we're removing less than the total count of the item, just subtract the amount
		if (AmountToRemove < ItemCountArray[IndexOfItem])
		{
			ItemCountArray[IndexOfItem] -= AmountToRemove;
		}
		// Otherwise remove the whole item from the loot box
		else
		{
			ItemRefArray.RemoveAt(IndexOfItem);
			ItemCountArray.RemoveAt(IndexOfItem);
		}
	}
}

void ULootBox::AddItem(UDA_Item* ItemToAdd, int NumToAdd)
{
	// Try to find the index of the item in the loot box
	int IndexOfItem = ItemRefArray.Find(ItemToAdd);

	// Check if the item already exists in the loot box
	if (IndexOfItem != INDEX_NONE)
	{
		// If it does, just add the amount to the existing count
		ItemCountArray[IndexOfItem] += NumToAdd;
	}
	// Otherwise add the item to the loot box
	else
	{
		ItemRefArray.Add(ItemToAdd);
		ItemCountArray.Add(NumToAdd);
	}
}

