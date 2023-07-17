// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "InventoryItem.h"


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
bool UInventory::AddToInventory(UInventoryItem Item)
{
	// if number of items in inventory is less than inventory size then add item to inventory
	if (Inventory.Num() >= InventorySize)
	{
		UE_LOG(LogTemp, Display, TEXT("Inventory full. Cannot add item. See Inventory, AddItem"));
		return false;
	}

	// If the inventory is empty, just create a new item
	if (Inventory.Num() == 0)
	{
		Inventory.Add(&Item);
		return true;
	}

	// If the item is stackable and already in the inventory then just increase the quantity
	bool IsStackable = Item.MaxStackSize > 1;

	// Add item to the first matching slot that isn't maxed out
	for (int idx = 0; idx < Inventory.Num(); idx++)
	{
		// If the item already exists in the inventory and isn't maxed out, add to it
		if (Inventory[idx]->ItemName == Item.ItemName && Inventory[idx]->Quantity < Item.MaxStackSize)
		{
			Inventory[idx]->Quantity += 1;
			return true;
		}
		// Otherwise add a new item slot to the inventory
		else
		{
			Inventory.Add(&Item);
			return true;
		}
	}

	// Technically we should never reach this point, but if we have then something went wrong
	UE_LOG(LogTemp, Error, TEXT("Something went wrong trying to add item to inventory. See Inventory, AddItem"));
	return false;
}

void UInventory::RemoveFromInventory(UInventoryItem Item)
{
	// Find item in inventory and remove it
	for (int idx = 0; idx < Inventory.Num(); idx++)
	{
		if (Inventory[idx]->ItemName == Item.ItemName)
		{
			// If there's more than one of said item, remove one (by reducing the quantity)
			if (Inventory[idx]->Quantity > 1)
			{
				Inventory[idx]->Quantity -= 1;
				return;
			}
			// Otherwise remove the entire item from the inventory
			else
			{
				Inventory.RemoveAt(idx);
				return;
			}
		}
	}
}

int UInventory::GetInventorySize()
{
	return InventorySize;
}


