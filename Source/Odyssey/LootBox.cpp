// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBox.h"
#include "WBP_InventorySlot.h"

ULootBox::ULootBox()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void ULootBox::BeginPlay()
{
	Super::BeginPlay();

	// We need to make sure each item also has a corresponding count, so we make sure the arrays are the same size
	if (ItemRefArray.Num() != ItemCountArray.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("ULootBox::BeginPlay: Item and ItemCount arrays are not the same size!"));
		return;		
	}
}

void ULootBox::RemoveItem(UDA_Item* ItemToRemove, int AmountToRemove)
{
	int IndexOfItem = ItemRefArray.Find(ItemToRemove);

	if (IndexOfItem != INDEX_NONE)  // make sure the item actually exists in the loot box
	{
		if (AmountToRemove < ItemCountArray[IndexOfItem]) // Reduce the item count
		{
			ItemCountArray[IndexOfItem] -= AmountToRemove;
		}
		else  // Remove the whole item
		{
			ItemRefArray.RemoveAt(IndexOfItem);
			ItemCountArray.RemoveAt(IndexOfItem);
		}
	}
}

void ULootBox::AddItem(UDA_Item* ItemToAdd, int NumToAdd)
{
	int IndexOfItem = ItemRefArray.Find(ItemToAdd);

	if (IndexOfItem != INDEX_NONE)  // make sure the item actually exists in the loot box
	{
		ItemCountArray[IndexOfItem] += NumToAdd;  // Increase the item count
	}
	else  // Add new item to the loot box
	{
		ItemRefArray.Add(ItemToAdd);
		ItemCountArray.Add(NumToAdd);
	}
}

