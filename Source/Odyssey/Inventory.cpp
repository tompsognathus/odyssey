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
int UInventory::AddSlotContentsToInventory(UWBP_InventorySlot* &InventorySlot)
{
	int NumAdded = 0;

	UDA_Item* ItemToAdd = InventorySlot->GetItem();
	int NumToAdd = InventorySlot->GetStackSize();
	int NumEmptySlots = GetNumEmptyInventorySlots();

	// Try to find the index of the item in the inventory
	int IndexOfItem = ItemRefArray.Find(ItemToAdd);

	// Find all instances of the item in the inventory and count them
	int NumAlreadyInInventory = 0;
	for (int idx = 0; idx < ItemRefArray.Num(); idx++)
	{
		if (ItemRefArray[idx] == ItemToAdd)
		{
			NumAlreadyInInventory += ItemCountArray[idx];
		}
	}

	// Based on the max stack size for this item, determine how many more items can be added to the stacks already in the inventory
	if (ItemToAdd)
	{
		int AvailableSpaceOnExistingStacks = NumAlreadyInInventory % ItemToAdd->MaxStackSize;

		int AvailableSpaceOnEmptySlots = NumEmptySlots * ItemToAdd->MaxStackSize;

		// Add as many of the item as there is space for on existing and empty slots
		NumAdded = FMath::Min(NumToAdd, AvailableSpaceOnExistingStacks + AvailableSpaceOnEmptySlots);

		ItemCountArray[IndexOfItem] += NumAdded;

	} else { UE_LOG(LogTemp, Warning, TEXT("ItemToAdd is null. See Inventory, AddSlotContentsToInventory")); }

	// Enable the slot so it's clickable again
	InventorySlot->SetSlotIsEnabled(true);

	return NumAdded;
}

int UInventory::GetNumEmptyInventorySlots()
{
	int NumSlotsTaken = 0;

	for (int idx = 0; idx < ItemRefArray.Num(); idx++)
	{
		NumSlotsTaken += FMath::CeilToInt((float)ItemCountArray[idx] / (float)ItemRefArray[idx]->MaxStackSize);
	}

	int NumSlotsAvailable = MaxInventorySize - NumSlotsTaken;

	return NumSlotsAvailable;
}

int UInventory::GetMaxInventorySize()
{
	return MaxInventorySize;
}

int UInventory::GetNumItems()
{
	return ItemRefArray.Num();
}

void UInventory::RemoveItem(UDA_Item* ItemToRemove, int AmountToRemove)
{
	// Find item in inventory
	int IndexOfItemToRemove = ItemRefArray.Find(ItemToRemove);

	// If the item is in the inventory, remove it and its count from the count array
	if (IndexOfItemToRemove != INDEX_NONE)
	{
		ItemRefArray.RemoveAt(IndexOfItemToRemove);
		ItemCountArray.RemoveAt(IndexOfItemToRemove);
	}
}


