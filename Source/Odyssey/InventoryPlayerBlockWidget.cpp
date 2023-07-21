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
}

void UInventoryPlayerBlockWidget::UpdateGridContents()
{
	// Clear inventory grid
	InventoryGrid->ClearChildren();

	// Get actual inventory contents from inventory
	TArray<class UDA_Item*> InventoryItemRefs = Inventory->GetItemRefArray();
	TArray<int> InventoryItemStackSizes = Inventory->GetItemStackSizes();

	// Populate grid with inventory slot widgets
	int InventorySize = Inventory->GetInventorySize();
	for (int idx = 0; idx < InventorySize; idx++)
	{
		UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);

		// Add to grid
		InventoryGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);
	}

	// Update inventory slot widgets with item data
	for (int idx = 0; idx < InventoryItemRefs.Num(); idx++)
	{
		UDA_Item* Item = InventoryItemRefs[idx];
		int ItemStackSize = InventoryItemStackSizes[idx];

		// Get item info
		EItemNames ItemName = Item->Name;
		FString ItemDisplayName = Item->DisplayName;
		FString ItemDescription = Item->Description;
		UTexture2D* ItemIcon = Item->Icon;
		int MaxStackSize = Item->MaxStackSize;

		// Calculate the number of slots this item will take up
		int NumSlots = FMath::CeilToInt((float)ItemStackSize / (float)MaxStackSize);

		while (NumSlots > 0)
		{
			// Get the next available inventory slot
			for (int slotIdx = 0; slotIdx < InventorySize; slotIdx++)
			{
				// Get inventory slot widget
				UWBP_InventorySlot* InventorySlotWidget = Cast<UWBP_InventorySlot>(InventoryGrid->GetChildAt(slotIdx));

				// Check if slot is empty
				if (InventorySlotWidget->GetItemName() == EItemNames::VE_None)
				{
					// Set item info
					InventorySlotWidget->SetItemName(ItemName);
					InventorySlotWidget->SetItemImg(ItemIcon);
					// If we're breaking up the item into multiple stacks, all but the last one will be full
					if (NumSlots > 1)
					{
						InventorySlotWidget->SetStackSizeText(FText::FromString(FString::FromInt(MaxStackSize)));
					}
					else
					{
						// Compute remainder of stack size
						int StackRemainder = ItemStackSize % MaxStackSize;
						InventorySlotWidget->SetStackSizeText(FText::FromString(FString::FromInt(StackRemainder)));
					}

					// Break out of loop as we've now populated the next available slot
					break;
				}
			}
			NumSlots--;
		}

	}
}
