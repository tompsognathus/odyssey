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

	// bind delegate to double clicking slots
	if (WBP_InventoryPlayerBlock)
	{
		WBP_InventoryPlayerBlock->OnInventorySlotDoubleClickedDelegate.AddDynamic(this, &UTradingInventoryWidget::OnInventorySlotDoubleClicked);

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryPlayerBlock in TradingInventoryWidget, NativeConstruct")); }

	if (WBP_InventoryLootBoxBlock)
	{
		WBP_InventoryLootBoxBlock->OnInventorySlotDoubleClickedDelegate.AddDynamic(this, &UTradingInventoryWidget::OnInventorySlotDoubleClicked);

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryLootBoxBlock in TradingInventoryWidget, NativeConstruct")); }
}

void UTradingInventoryWidget::LoadPlayerInventoryUIContents()
{
	if (WBP_InventoryPlayerBlock)
	{
		// Populate inventory grid with player inventory contents
		WBP_InventoryPlayerBlock->LoadInventoryGridContents(Inventory->GetItemRefArray(), Inventory->GetItemCountArray(), Inventory->GetMaxInventorySize());

		
	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryPlayerBlock in TradingInventoryWidget, UpdatePlayerInventoryUIContents")); }
}

void UTradingInventoryWidget::LoadLootBoxInventoryUIContents(ULootBox* LootBox)
{
	if (WBP_InventoryLootBoxBlock)
	{
		CurrentLootBox = LootBox;

		// Populate inventory grid with loot box contents
		WBP_InventoryLootBoxBlock->LoadInventoryGridContents(LootBox->GetItemRefArray(), LootBox->GetItemCountArray(), LootBox->GetMaxInventorySize());

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryLootBoxBlock in TradingInventoryWidget, UpdateAvailableLootUIContents")); }
}


void UTradingInventoryWidget::OnInventorySlotDoubleClicked(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot)
{
	UDA_Item* Item = InventorySlot->GetItem();

	// First make sure the slot isn't empty
	if (Item == nullptr) { return; }
	if (CurrentLootBox == nullptr) { 
		UE_LOG(LogTemp, Error, TEXT("CurrentLootBox is null. See TradingInventoryWidget, OnInventorySlotDoubleClicked. Did you get a reference when opening the UI?"));
		return;
	}

	// Figure out whether the clicked slot is in the player inventory or the loot box inventory
	if (InventoryBlockWidget == WBP_InventoryPlayerBlock)
	{
		OnPlayerInventorySlotDoubleClicked(InventorySlot);
	}
	else if (InventoryBlockWidget == WBP_InventoryLootBoxBlock)
	{
		OnLootBoxInventorySlotDoubleClicked(InventorySlot);

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find InventoryGrid in TradingInventoryWidget, OnInventorySlotDoubleClicked")); }

}

void UTradingInventoryWidget::OnPlayerInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	UE_LOG(LogTemp, Warning, TEXT("Player inventory slot double clicked"));

	UDA_Item* Item = InventorySlot->GetItem();







}

void UTradingInventoryWidget::OnLootBoxInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	UE_LOG(LogTemp, Warning, TEXT("Loot box inventory slot double clicked"));

	UDA_Item* Item = InventorySlot->GetItem();

	// Offer item to inventory
	int NumAdded = Inventory->AddSlotContentsToInventory(InventorySlot);

	if (NumAdded > 0)
	{
		// Add item to player inventory
		Inventory->AddSlotContentsToInventory(InventorySlot);

		// Update Inventory UI grid
		WBP_InventoryPlayerBlock->AddSlotContentsToInventoryGrid(InventorySlot);

		// Remove item from loot box grid
		WBP_InventoryLootBoxBlock->RemoveSlotContentsFromInventoryGrid(InventorySlot);

		// Remove item from loot box
		CurrentLootBox->RemoveItem(Item, NumAdded);

	}
	else { UE_LOG(LogTemp, Warning, TEXT("Cannot add item to inventory. Perhaps it's full? See TradingInventoryWidget, OnLootBoxInventorySlotDoubleClicked")); }

}