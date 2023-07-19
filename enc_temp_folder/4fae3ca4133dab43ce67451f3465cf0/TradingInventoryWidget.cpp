// Fill out your copyright notice in the Description page of Project Settings.


#include "TradingInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "UIManager.h"
#include "Inventory.h"
#include "LootBox.h"


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
}

void UTradingInventoryWidget::UpdateAvailableLootUIContents(ULootBox* LootBox)
{
	// Clear inventory grid
	AvailableLootGrid->ClearChildren();

	// Figure out how many items are available and how many rows of slots we need
	TArray<class UDA_Item*> LootableItemRefs = LootBox->GetLootableItemRefArray();

	int NumLootableItems = LootableItemRefs.Num();
	int NumLootableItemRows = NumLootableItems / NumInventoryCols;
	if (NumLootableItems % NumInventoryCols != 0) { NumLootableItemRows++; }

	// Populate available loot grid with inventory slot widgets
	for (int idx = 0; idx < NumLootableItems; idx++)
	{
		UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);
		// Add to grid
		AvailableLootGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);
	}
}
