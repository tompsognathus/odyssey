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
	}
}

void UInventoryPlayerBlockWidget::LoadInventoryGridContents(TArray<class UDA_Item*> ItemRefArray, TArray<int> ItemCountArray)
{
	// Clear inventory grid
	InventoryGrid->ClearChildren();

	int NumSlots = ItemRefArray.Num();
	UDA_Item* ItemToAdd = nullptr;
	int ItemCount = 0;

	UE_LOG(LogTemp, Warning, TEXT("NumSlots: %d"), NumSlots);

	// Populate available loot grid with inventory slot widgets
	for (int idx = 0; idx < NumSlots; idx++)
	{
		ItemToAdd = ItemRefArray[idx];
		ItemCount = ItemCountArray[idx];

		AddItemToGrid(ItemToAdd, ItemCount);
	}
}

void UInventoryPlayerBlockWidget::AddItemToGrid(UDA_Item* ItemToAdd, int ItemCount)
{
	UWBP_InventorySlot* InventorySlot = nullptr;

	// If the item already exists in the grid, find it and add to the count
	for (int idx = 0; idx < InventoryGrid->GetChildrenCount(); idx++)
	{
		InventorySlot = Cast<UWBP_InventorySlot>(InventoryGrid->GetChildAt(idx));
		if (InventorySlot->GetItem() == ItemToAdd)
		{
			InventorySlot->SetStackSize(InventorySlot->GetNumItems() + ItemCount);
			break;
		}
	}
	// Otherwise create a new slot
	UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);
	InventorySlot = Cast<UWBP_InventorySlot>(InventorySlotWidget);

	if (InventorySlot)
	{
		// Compute index for this new slot
		int idx = InventoryGrid->GetChildrenCount();

		// Compute its row/column
		int SlotRow = idx / NumInventoryCols;
		int SlotCol = idx % NumInventoryCols;
	
		// Add to grid
		InventoryGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);
		InventorySlot->SetItem(ItemToAdd, ItemCount);

		// Bind functions to On Double Clicked event in inventory slot widget
		InventorySlot->OnDoubleClicked.AddDynamic(this, &UInventoryPlayerBlockWidget::OnInventorySlotDoubleClicked);

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot cast InventorySlotWidget to UWBP_InventorySlot in InventoryWidget, AddItemToGrid")); }
}

void UInventoryPlayerBlockWidget::RemoveItemFromGrid(UDA_Item* ItemToRemove, int NumToRemove)
{
	// Find slot in grid
	for (int idx = 0; idx < InventoryGrid->GetChildrenCount(); idx++)
	{
		UWBP_InventorySlot* InventorySlot = Cast<UWBP_InventorySlot>(InventoryGrid->GetChildAt(idx));
		if (InventorySlot)
		{
			if (InventorySlot->GetItem() == ItemToRemove)
			{
				// If we are removing less than the total number of items in the slot, remove that many but keep the slot
				if (NumToRemove < InventorySlot->GetNumItems())
				{
					InventorySlot->SetItem(ItemToRemove, InventorySlot->GetNumItems() - NumToRemove);
					return;
				}
				// Otherwise remove the whole slot
				else
				{
					InventoryGrid->RemoveChildAt(idx);
					return;
				}
			}
		} else { UE_LOG(LogTemp, Error, TEXT("Cannot cast InventorySlotWidget to UWBP_InventorySlot in InventoryWidget, RemoveItemFromGrid")); }
	}
}

void UInventoryPlayerBlockWidget::OnInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	// broadcast event
	OnInventorySlotDoubleClickedDelegate.Broadcast(this, InventorySlot);

}

 