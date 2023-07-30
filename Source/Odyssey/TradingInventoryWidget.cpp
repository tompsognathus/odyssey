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
		// Populate inventory grid with loot box contents
		WBP_InventoryLootBoxBlock->LoadInventoryGridContents(LootBox->GetItemRefArray(), LootBox->GetItemCountArray(), LootBox->GetMaxInventorySize());

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryLootBoxBlock in TradingInventoryWidget, UpdateAvailableLootUIContents")); }
}


void UTradingInventoryWidget::OnInventorySlotDoubleClicked(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot)
{
	UDA_Item* Item = InventorySlot->GetItem();

	// First make sure the slot isn't empty
	if (Item == nullptr) { return; }

	// Figure out whether the clicked slot is in the player inventory or the loot box inventory
	if (InventoryBlockWidget == WBP_InventoryPlayerBlock)
	{
		OnPlayerInventorySlotDoubleClicked();
	}
	else if (InventoryBlockWidget == WBP_InventoryLootBoxBlock)
	{
		OnLootBoxInventorySlotDoubleClicked();

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find InventoryGrid in TradingInventoryWidget, OnInventorySlotDoubleClicked")); }

}

void UTradingInventoryWidget::OnPlayerInventorySlotDoubleClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Player inventory slot double clicked"));
}

void UTradingInventoryWidget::OnLootBoxInventorySlotDoubleClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Loot box inventory slot double clicked"));
}