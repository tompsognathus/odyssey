// Fill out your copyright notice in the Description page of Project Settings.


#include "TradingInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "UIManager.h"
#include "Inventory.h"
#include "LootBox.h"
#include "DA_Item.h"
#include "WBP_InventorySlot.h"
#include "InventoryPlayerBlockWidget.h"


void UTradingInventoryWidget::NativeConstruct()
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
}

void UTradingInventoryWidget::LoadPlayerInventoryUIContents()
{
	if (WBP_InventoryPlayerBlock)
	{
		WBP_InventoryPlayerBlock->LoadInventoryGridContents();

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryPlayerBlock in TradingInventoryWidget, UpdatePlayerInventoryUIContents")); }
}

void UTradingInventoryWidget::LoadAvailableLootUIContents(ULootBox* LootBox)
{
	CurrentLootBox = LootBox;

	// Clear inventory grid
	AvailableLootGrid->ClearChildren();

	// Figure out how many items are available and how many rows of slots we need
	TArray<class UDA_Item*> LootableItemRefs = LootBox->GetLootableItemRefArray();
	TArray<int> LootableItemStackSizes = LootBox->GetLootableItemStackSizes();

	// Calculate how many slots we need once items have been broken into stacks of max size
	int NumRequiredSlots = 0;
	for (int idx = 0; idx < LootableItemRefs.Num(); idx++)
	{
		NumRequiredSlots += FMath::CeilToInt((float)LootableItemStackSizes[idx] / (float)LootableItemRefs[idx]->MaxStackSize);
	}

	// Calculate how many rows of slots we need
	int NumLootableItemRows = NumRequiredSlots / NumInventoryCols;
	if (NumRequiredSlots % NumInventoryCols != 0) { NumLootableItemRows++; }

	// Calculate how many slots we need, including empty slots to fill the last row
	NumLootBoxSlots = NumLootableItemRows * NumInventoryCols;

	// Populate available loot grid with inventory slot widgets
	for (int idx = 0; idx < NumLootBoxSlots; idx++)
	{
		AddInventorySlotToGrid(idx);
	}

	// Populate available loot grid with lootable item info
	for (int idx = 0; idx < LootableItemRefs.Num(); idx++)
	{
		// Get item and stack size
		UDA_Item* Item = LootableItemRefs[idx];
		int ItemCount = LootableItemStackSizes[idx];
		int MaxStackSize = Item->MaxStackSize;

		// Calculate the number of slots this item will take up
		int NumSlotsToFill = FMath::CeilToInt((float)ItemCount / (float)MaxStackSize);

		while (NumSlotsToFill > 0)
		{
			// Get the next available inventory slot
			for (int slotIdx = 0; slotIdx < NumLootBoxSlots; slotIdx++)
			{
				// Get inventory slot widget
				UWBP_InventorySlot* InventorySlotWidget = Cast<UWBP_InventorySlot>(AvailableLootGrid->GetChildAt(slotIdx));

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

void UTradingInventoryWidget::AddInventorySlotToGrid(int idx)
{
	UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);

	int SlotRow = idx / NumInventoryCols;
	int SlotCol = idx % NumInventoryCols;

	// Add to grid
	AvailableLootGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);

	// Bind functions to On Double Clicked event in inventory slot widget
	UWBP_InventorySlot* LootableSlot = Cast<UWBP_InventorySlot>(InventorySlotWidget);
	if (LootableSlot)
	{
		LootableSlot->OnDoubleClicked.AddDynamic(this, &UTradingInventoryWidget::OnLootableSlotDoubleClicked);

	}
	else { UE_LOG(LogTemp, Error, TEXT("Cannot cast InventorySlotWidget to UWBP_InventorySlot in InventoryWidget, CreateGridContent")); }
}

void UTradingInventoryWidget::RemoveSlotContents(UWBP_InventorySlot* InventorySlot)
{
	// Get slot contents
	UDA_Item* ItemToRemove = InventorySlot->GetItem();
	int NumToRemove = InventorySlot->GetStackSize();

	/***** Remove the item from the LootBox itself *****/
	if (CurrentLootBox)
	{
		CurrentLootBox->RemoveItem(ItemToRemove, NumToRemove);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find Inventory and therefore cannot remove slot contents in TradingInventoryWidget, RemoveSlotContents"));
		return;
	}

	/***** Remove the item from the UI *****/
	
	// Find slot in grid
	int SlotIndex = AvailableLootGrid->GetChildIndex(InventorySlot);

	// Clear slot
	InventorySlot->SetItem(nullptr, 0);
}

void UTradingInventoryWidget::OnLootableSlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	UE_LOG(LogTemp, Warning, TEXT("Double clicked lootable slot"));
	
	// First make sure the slot isn't empty
	if (InventorySlot->GetItem() == nullptr) { return; }

	// Remove slot contents from loot box grid
	RemoveSlotContents(InventorySlot);

	// And add it to the inventory
	//Inventory->AddToInventory(InventorySlot);

	// And add it to the inventory grid

}