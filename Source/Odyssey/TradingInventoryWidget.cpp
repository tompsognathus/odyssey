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
		WBP_InventoryPlayerBlock->PopulateGridWithSlots();

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

	int NumLootableItems = LootableItemRefs.Num();
	int NumLootableItemRows = NumLootableItems / NumInventoryCols;
	if (NumLootableItems % NumInventoryCols != 0) { NumLootableItemRows++; }

	NumLootBoxSlots = NumLootableItemRows * NumInventoryCols;

	// Populate available loot grid with inventory slot widgets
	for (int idx = 0; idx < NumLootBoxSlots; idx++)
	{
		AddInventorySlotToGrid(idx);
	}

	// Populate available loot grid with lootable item info
	for (int idx = 0; idx < NumLootableItems; idx++)
	{
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

void UTradingInventoryWidget::RemoveSlotContents(UDA_Item* ItemToRemove, int NumToRemove)
{
	// Remove the item from the LootBox itself
	if (CurrentLootBox)
	{
		CurrentLootBox->RemoveItem(ItemToRemove, NumToRemove);
	}

	// Remove the item from the UI
	
	// Search from end of array to beginning to find the item to remove
	for (int idx = NumLootBoxSlots - 1; idx >= 0; idx--)
	{
		// print idx
		UE_LOG(LogTemp, Warning, TEXT("idx: %d"), idx);
		// Get the slot widget at idx
		UWBP_InventorySlot* InventorySlotWidget = Cast<UWBP_InventorySlot>(AvailableLootGrid->GetChildAt(idx));
		if (InventorySlotWidget)
		{
			UDA_Item* ItemInSlot = InventorySlotWidget->GetItem();

			if (ItemInSlot == nullptr)
			{
				// If the slot is empty, continue to the next one
				continue;
			}

			bool bNamesMatch = ItemInSlot->Name == ItemToRemove->Name;

			if (bNamesMatch)
			{

				int ItemStackSize = InventorySlotWidget->GetStackSize();

				// If there are fewer items to remove than there are in the slot, simply reduce the stack size of the slot
				if (NumToRemove < ItemStackSize)
				{
					InventorySlotWidget->SetStackSize(InventorySlotWidget->GetStackSize() - NumToRemove);
					break;
				}
				// If the number of items to remove matches the number of items in the slot, remove the entire slot and add a new one
				// in its place
				else if (NumToRemove == ItemStackSize)
				{
					// Remove the slot from the grid
					AvailableLootGrid->RemoveChildAt(idx);
					
					// Add a new slot to replace it
					AddInventorySlotToGrid(idx);
				}
			}
		} else { UE_LOG(LogTemp, Error, TEXT("Cannot cast InventorySlotWidget to UWBP_InventorySlot in InventoryWidget, RemoveItem")); }
	}
}

void UTradingInventoryWidget::OnLootableSlotDoubleClicked(UDA_Item* Item, int StackSize)
{
	RemoveSlotContents(Item, StackSize);
	//Inventory->AddToInventory(Item, StackSize);
	UE_LOG(LogTemp, Warning, TEXT("Double clicked lootable slot"));
}