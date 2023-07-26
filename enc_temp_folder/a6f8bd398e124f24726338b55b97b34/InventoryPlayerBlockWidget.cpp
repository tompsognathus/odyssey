// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPlayerBlockWidget.h"

#include "Components/UniformGridPanel.h"
#include "Inventory.h"
#include "UIManager.h"
#include "DA_Item.h"
#include "WBP_InventorySlot.h"
#include "ItemNames.h"


void UInventoryPlayerBlockWidget::NativeConstruct()
{
	// Get player pawn
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		// Get UI Manager component
		UIManager = Cast<UUIManager>(PlayerPawn->GetComponentByClass(UUIManager::StaticClass()));

		if (!UIManager) { UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in InventoryWidget, NativeConstruct")); }

		// Get inventory component
		Inventory = Cast<UInventory>(PlayerPawn->GetComponentByClass(UInventory::StaticClass()));

		if (!Inventory) { UE_LOG(LogTemp, Error, TEXT("Cannot find Inventory in InventoryWidget, NativeConstruct")); }
	}

	// Bind to inventory update event
	Inventory->OnInventoryUpdated.AddDynamic(this, &UInventoryPlayerBlockWidget::OnInventoryUpdated);
}

void UInventoryPlayerBlockWidget::LoadInventoryGridContents()
{
	// Clear inventory grid
	InventoryGrid->ClearChildren();

	// Get actual inventory contents from inventory
	TArray<class UDA_Item*> InventoryItemRefs = Inventory->GetItemRefArray();
	TArray<int> InventoryItemStackSizes = Inventory->GetItemStackSizes();

	// Populate grid with empty inventory slot widgets
	NumInventorySlots = Inventory->GetMaxInventorySize();

	// Populate available loot grid with inventory slot widgets
	for (int idx = 0; idx < NumInventorySlots; idx++)
	{
		AddInventorySlotToGrid(idx);
	}

	// Calculate how many slots we need once items have been broken into stacks of max size
	int NumSlotsNeeded = 0;
	for (int idx = 0; idx < InventoryItemRefs.Num(); idx++)
	{
		NumSlotsNeeded += FMath::CeilToInt((float)InventoryItemStackSizes[idx] / (float)InventoryItemRefs[idx]->MaxStackSize);
	}

	// Populate slots with items
	PopulateGridSlotsWithItems(InventoryItemRefs, InventoryItemStackSizes, NumSlotsNeeded);
}

void UInventoryPlayerBlockWidget::PopulateGridSlotsWithItems(TArray<UDA_Item*>& InventoryItemRefs, FJsonSerializableArrayInt& InventoryItemStackSizes, int NumSlotsNeeded)
{
	for (int idx = 0; idx < InventoryItemRefs.Num(); idx++)
	{
		// Get item and stack size
		UDA_Item* Item = InventoryItemRefs[idx];
		int ItemCount = InventoryItemStackSizes[idx];
		int MaxStackSize = Item->MaxStackSize;

		// Calculate the number of slots this item will take up
		int NumSlotsToFill = FMath::CeilToInt((float)ItemCount / (float)MaxStackSize);

		// Fill slots with this item
		while (NumSlotsToFill > 0)
		{
			// Get the next available inventory slot
			for (int slotIdx = 0; slotIdx < NumSlotsNeeded; slotIdx++)
			{
				// Get inventory slot widget
				UWBP_InventorySlot* InventorySlotWidget = Cast<UWBP_InventorySlot>(InventoryGrid->GetChildAt(slotIdx));

				// If we've reached the end of the inventory grid, warn and break. This shouldn't happen as
				// the inventory should never contain more content than it can hold.
				if (!InventorySlotWidget)
				{
					UE_LOG(LogTemp, Warning, TEXT("Inventory contains more items than it can hold! This should NOT happen. See InventoryPlayerBlockWidget, LoadInventoryGridContents"));
					return;
				}

				// Check if slot is empty
				if (InventorySlotWidget->GetItem() == nullptr)
				{
					// If we're breaking up the item into multiple stacks, all but the last one will be full
					if (NumSlotsToFill > 1)
					{
						InventorySlotWidget->SetItem(Item, MaxStackSize);
						ItemCount -= MaxStackSize;
					}
					else
					{
						InventorySlotWidget->SetItem(Item, ItemCount);
					}

					// Make the slot clickable
					InventorySlotWidget->SetSlotIsEnabled(true);

					NumSlotsToFill--;
					// Break out of loop as we've now populated the next available slot
					break;
				}
			}
		}
	}
}

void UInventoryPlayerBlockWidget::AddInventorySlotToGrid(int idx)
{
	UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);

	int SlotRow = idx / NumInventoryCols;
	int SlotCol = idx % NumInventoryCols;

	// Add to grid
	InventoryGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);

	// Bind functions to On Double Clicked event in inventory slot widget
	UWBP_InventorySlot* LootableSlot = Cast<UWBP_InventorySlot>(InventorySlotWidget);
	if (LootableSlot)
	{
		LootableSlot->OnDoubleClicked.AddDynamic(this, &UInventoryPlayerBlockWidget::OnInventorySlotDoubleClicked);

	}
	else { UE_LOG(LogTemp, Error, TEXT("Cannot cast InventorySlotWidget to UWBP_InventorySlot in InventoryWidget, CreateGridContent")); }
}

void UInventoryPlayerBlockWidget::RemoveSlotContents(UWBP_InventorySlot* InventorySlot)
{
	// Get slot contents
	UDA_Item* ItemToRemove = InventorySlot->GetItem();
	int NumToRemove = InventorySlot->GetStackSize();

	/***** Remove the item from the inventory itself *****/
	if (Inventory)
	{
		Inventory->RemoveItem(ItemToRemove, NumToRemove);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find Inventory and therefore cannot remove slot contents in InventoryWidget, RemoveSlotContents"));
		return;
	}

	/***** Remove the item from the UI *****/

	// Find slot in grid
	int SlotIndex = InventoryGrid->GetChildIndex(InventorySlot);

	// Clear slot
	InventorySlot->SetItem(nullptr, 0);
}


void UInventoryPlayerBlockWidget::OnInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	UE_LOG(LogTemp, Warning, TEXT("Double clicked inventory slot"));

	// First make sure the slot isn't empty
	if (InventorySlot->GetItem() == nullptr) { return; }

	// Remove slot contents from the inventory grid
	RemoveSlotContents(InventorySlot);

	//Inventory->AddToInventory(Item, StackSize);
}

void UInventoryPlayerBlockWidget::OnInventoryUpdated()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory updated"));
}