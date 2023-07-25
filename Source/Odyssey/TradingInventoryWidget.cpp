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
	// Clear inventory grid
	AvailableLootGrid->ClearChildren();

	// Figure out how many items are available and how many rows of slots we need
	TArray<class UDA_Item*> LootableItemRefs = LootBox->GetLootableItemRefArray();
	TArray<int> LootableItemStackSizes = LootBox->GetLootableItemStackSizes();

	int NumLootableItems = LootableItemRefs.Num();
	int NumLootableItemRows = NumLootableItems / NumInventoryCols;
	if (NumLootableItems % NumInventoryCols != 0) { NumLootableItemRows++; }

	NumSlots = NumLootableItemRows * NumInventoryCols;

	// Populate available loot grid with inventory slot widgets
	for (int idx = 0; idx < NumSlots; idx++)
	{
		UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);

		// Add to grid
		AvailableLootGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);

		// Bind functions to On Double Clicked event in inventory slot widget
		UWBP_InventorySlot* LootableSlot = Cast<UWBP_InventorySlot>(InventorySlotWidget);
		if (LootableSlot)
		{
			LootableSlot->OnDoubleClicked.AddDynamic(this, &UTradingInventoryWidget::OnLootableSlotDoubleClicked);

		} else { UE_LOG(LogTemp, Error, TEXT("Cannot cast InventorySlotWidget to UWBP_InventorySlot in InventoryWidget, CreateGridContent")); }
	}

	// Populate available loot grid with lootable item info
	for (int idx = 0; idx < NumLootableItems; idx++)
	{
		UDA_Item* Item = LootableItemRefs[idx];
		int ItemCount = LootableItemStackSizes[idx];
		int MaxStackSize = Item->MaxStackSize;

		// Calculate the number of slots this item will take up
		int NumSlotsToFill = FMath::CeilToInt((float)ItemCount / (float)MaxStackSize);

		// print num slots to fill
UE_LOG(LogTemp, Warning, TEXT("NumSlotsToFill: %d"), NumSlotsToFill);

		while (NumSlotsToFill > 0)
		{
			// Get the next available inventory slot
			for (int slotIdx = 0; slotIdx < NumSlots; slotIdx++)
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


void UTradingInventoryWidget::OnLootableSlotDoubleClicked(UDA_Item* Item, int StackSize)
{
	Inventory->AddToInventory(Item, StackSize);
	UE_LOG(LogTemp, Warning, TEXT("Double clicked lootable slot"));
}