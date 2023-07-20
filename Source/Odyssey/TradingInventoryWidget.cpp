// Fill out your copyright notice in the Description page of Project Settings.


#include "TradingInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "UIManager.h"
#include "Inventory.h"
#include "LootBox.h"
#include "DA_Item.h"
#include "WBP_InventorySlot.h"


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

void UTradingInventoryWidget::UpdatePlayerInventoryUIContents()
{
	// Clear inventory grid
	InventoryGrid->ClearChildren();

	// Populate inventory grid with inventory slot widgets
	int InventorySize = Inventory->GetInventorySize();
	for (int idx = 0; idx < InventorySize; idx++)
	{
		UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);
		// Add to grid
		InventoryGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);
	}

	// Populate inventory grid with items in inventory

}

void UTradingInventoryWidget::UpdateAvailableLootUIContents(ULootBox* LootBox)
{
	// Clear inventory grid
	AvailableLootGrid->ClearChildren();

	// Figure out how many items are available and how many rows of slots we need
	TArray<class UDA_Item*> LootableItemRefs = LootBox->GetLootableItemRefArray();
	TArray<int> LootableItemStackSizes = LootBox->GetLootableItemStackSizes();

	int NumLootableItems = LootableItemRefs.Num();
	int NumLootableItemRows = NumLootableItems / NumInventoryCols;
	if (NumLootableItems % NumInventoryCols != 0) { NumLootableItemRows++; }

	// Populate available loot grid with inventory slot widgets
	for (int idx = 0; idx < NumLootableItemRows * NumInventoryCols; idx++)
	{
		UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);

		// Add to grid
		AvailableLootGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);
	}

	// Populate available loot grid with lootable item info
	for (int idx = 0; idx < NumLootableItems; idx++)
	{
		UDA_Item* Item = LootableItemRefs[idx];
		int ItemStackSize = LootableItemStackSizes[idx];
		
		// Get item info
		EItemNames ItemName = Item->Name;
		FString ItemDisplayName = Item->DisplayName;
		FString ItemDescription = Item->Description;
		UTexture2D* ItemIcon = Item->Icon;
		int MaxStackSize = Item->MaxStackSize;

		// Get inventory slot
		UWidget* InventorySlotWidgetParent = AvailableLootGrid->GetChildAt(idx);
		if (InventorySlotWidgetParent)
		{
			// Cast to inventory slot widget
			UWBP_InventorySlot* InventorySlotWidget = Cast<UWBP_InventorySlot>(InventorySlotWidgetParent);

			if (InventorySlotWidget)
			{
				// Populate inventory slot info
				InventorySlotWidget->SetItemImg(ItemIcon);
				InventorySlotWidget->SetStackSizeText(FText::FromString(FString::FromInt(ItemStackSize)));

			} else { UE_LOG(LogTemp, Error, TEXT("Cannot cast inventory slot widget in TradingInventoryWidget, UpdateAvailableLootUIContents")); }
		} else { UE_LOG(LogTemp, Error, TEXT("Cannot get inventory slot child from grid in TradingInventoryWidget, UpdateAvailableLootUIContents")); }
	}
}
