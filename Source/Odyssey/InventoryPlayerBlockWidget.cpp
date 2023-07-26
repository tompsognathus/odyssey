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

void UInventoryPlayerBlockWidget::PopulateGridWithSlots()
{
	// Clear inventory grid
	InventoryGrid->ClearChildren();

	// Get actual inventory contents from inventory
	TArray<class UDA_Item*> InventoryItemRefs = Inventory->GetItemRefArray();
	TArray<int> InventoryItemStackSizes = Inventory->GetItemStackSizes();

	// Populate grid with empty inventory slot widgets
	NumInventorySlots = Inventory->GetMaxInventorySize();

	for (int idx = 0; idx < NumInventorySlots; idx++)
	{
		UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);

		// Add to grid
		InventoryGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);

		// Bind functions to On Double Clicked event in inventory slot widget
		UWBP_InventorySlot* InventorySlot = Cast<UWBP_InventorySlot>(InventorySlotWidget);
		if (InventorySlot)
		{
			InventorySlot->OnDoubleClicked.AddDynamic(this, &UInventoryPlayerBlockWidget::OnInventorySlotDoubleClicked);

		} else { UE_LOG(LogTemp, Error, TEXT("Cannot cast InventorySlotWidget to UWBP_InventorySlot in InventoryWidget, CreateGridContent")); }
	}

	// Fill grid with contents from inventory

}

void UInventoryPlayerBlockWidget::FillGridWithContentsFromInventory()
{
	// Get the number of items in the inventory
	int NumItems = Inventory->GetNumItems();
	TArray<class UDA_Item*> InventoryItemRefs = Inventory->GetItemRefArray();
	TArray<int> InventoryItemStackSizes = Inventory->GetItemStackSizes();

	// Update inventory slot widgets with item data
	for (int idx = 0; idx < NumItems; idx++)
	{
		UDA_Item* Item = InventoryItemRefs[idx];
		int ItemStackSize = InventoryItemStackSizes[idx];
		int MaxStackSize = Item->MaxStackSize;

		// Calculate the number of slots this item will take up
		int NumSlotsToFill = FMath::CeilToInt((float)ItemStackSize / (float)MaxStackSize);

		while (NumSlotsToFill > 0)
		{
			// Get the next available inventory slot
			for (int slotIdx = 0; slotIdx < NumInventorySlots; slotIdx++)
			{
				// Get inventory slot widget
				UWBP_InventorySlot* InventorySlotWidget = Cast<UWBP_InventorySlot>(InventoryGrid->GetChildAt(slotIdx));

				// Check if slot is empty
				if (InventorySlotWidget->GetItem() == nullptr)
				{
					// If we're breaking up the item into multiple stacks, all but the last one will be full
					if (NumSlotsToFill > 1)
					{
						InventorySlotWidget->SetItem(Item, MaxStackSize);
					}
					else
					{
						// Compute remainder of stack size
						int StackRemainder = ItemStackSize % MaxStackSize;
						InventorySlotWidget->SetItem(Item, StackRemainder);
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



void UInventoryPlayerBlockWidget::OnInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	UE_LOG(LogTemp, Warning, TEXT("Double clicked inventory slot"));
	//Inventory->AddToInventory(Item, StackSize);
}

void UInventoryPlayerBlockWidget::OnInventoryUpdated()
{
	UE_LOG(LogTemp, Warning, TEXT("Inventory updated"));
	FillGridWithContentsFromInventory();
}