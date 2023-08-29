// Fill out your copyright notice in the Description page of Project Settings.


#include "TradingInventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "UIManager.h"
#include "Inventory.h"
#include "LootBox.h"
#include "DA_Item.h"
#include "WBP_InventorySlot.h"
#include "InventoryPlayerBlockWidget.h"
#include "Components/SizeBox.h"
#include "Utility.h"
#include "Components/TextBlock.h"

void UTradingInventoryWidget::NativeConstruct()
{
	UIManager = Utility::GetUIManager(this);
	Inventory = Utility::GetInventory(this);

	if (!IsValid(WBP_InventoryPlayerBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::NativeConstruct: Invalid WBP_InventoryPlayerBlock on %s"), *GetName());
		return;
	}
	if (!IsValid(WBP_InventoryLootBoxBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::NativeConstruct: Invalid WBP_InventoryLootBoxBlock on %s"), *GetName());
		return;
	}

	WBP_InventoryPlayerBlock->OnInventorySlotDoubleClickedDelegate.AddDynamic(this, &UTradingInventoryWidget::OnInventorySlotDoubleClicked);
	WBP_InventoryLootBoxBlock->OnInventorySlotDoubleClickedDelegate.AddDynamic(this, &UTradingInventoryWidget::OnInventorySlotDoubleClicked);

	SetWidthForInventoryGrids();

}

void UTradingInventoryWidget::SetWidthForInventoryGrids()
{
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::SetWidthForInventoryGrids: Invalid UIManager on %s"), *GetName());
		return;
	}

	int InventorySlotWidth = 100;

	// Create an empty slot widget to get its size
	TSubclassOf<class UUserWidget> InventorySlotAssetRef = UIManager->InventorySlotAssetRef;
	if (!IsValid(InventorySlotAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::SetWidthForInventoryGrids: Invalid InventorySlotAssetRef on %s. Did you assign one in the editor?"), *GetName());
		return;
	}

	UWBP_InventorySlot* EmptySlot = CreateWidget<UWBP_InventorySlot>(this, InventorySlotAssetRef);
	if (!IsValid(EmptySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::SetWidthForInventoryGrids: Invalid EmptySlot"));
		return;
	}

	InventorySlotWidth = EmptySlot->GetWidth();

	int GridWidth = NumInventoryCols * InventorySlotWidth;
	// Set the width override for both grids based on the number of columns and the size of the slots
	if (!IsValid(PlayerInventorySizeBox))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::SetWidthForInventoryGrids: Invalid PlayerInventorySizeBox"));
		return;
	}
	if (!IsValid(LootInventorySizeBox))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::SetWidthForInventoryGrids: Invalid LootInventorySizeBox"));
		return;
	}

	PlayerInventorySizeBox->SetWidthOverride(GridWidth);
	LootInventorySizeBox->SetWidthOverride(GridWidth);
}

void UTradingInventoryWidget::LoadPlayerInventoryUIContents()
{
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::LoadPlayerInventoryUIContents: Invalid Inventory on %s. Does it have an inventory component?"), *GetName());
		return;
	}
	if (!IsValid(WBP_InventoryPlayerBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::LoadPlayerInventoryUIContents: Invalid WBP_InventoryPlayerBlock on %s. Did you assign it in the editor?"), *GetName());
		return;
	}

	// Populate inventory grid with player inventory contents
	WBP_InventoryPlayerBlock->LoadInventoryGridContents(Inventory->GetItemRefArray(), Inventory->GetItemCountArray());
}

void UTradingInventoryWidget::LoadLootBoxInventoryUIContents(ULootBox* LootBox)
{
	if (!IsValid(LootBox))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::LoadLootBoxInventoryUIContents: Invalid LootBox on %s"), *GetName());
		return;
	}
	if (!IsValid(WBP_InventoryLootBoxBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::LoadLootBoxInventoryUIContents: Invalid WBP_InventoryLootBoxBlock on %s"), *GetName());
		return;
	}
	CurrentLootBox = LootBox;

	// Populate inventory grid with loot box contents
	WBP_InventoryLootBoxBlock->LoadInventoryGridContents(LootBox->GetItemRefArray(), LootBox->GetItemCountArray());
}

void UTradingInventoryWidget::SetLootBoxNameText(FText NewLootBoxName)
{
	LootBoxNameText->SetText(NewLootBoxName);
}

void UTradingInventoryWidget::HandleTakeAllButtonClicked()
{
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::HandleTakeAllButtonClicked: Invalid Inventory on %s. Does it have an inventory component?"), *GetName());
		return;
	}
	if (!IsValid(CurrentLootBox))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::HandleTakeAllButtonClicked: Invalid CurrentLootBox on %s"), *GetName());
		return;
	}

	int NumItems = CurrentLootBox->GetItemRefArray().Num();
	TArray<UDA_Item*> ItemRefArray = CurrentLootBox->GetItemRefArray();
	TArray<int> ItemCountArray = CurrentLootBox->GetItemCountArray();

	for (int i = 0; i < NumItems; i++)
	{
		UDA_Item* Item = ItemRefArray[i];
		int ItemCount = ItemCountArray[i];

		if (!IsValid(Item))
		{
			UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::HandleTakeAllButtonClicked: Invalid Item in CurrentLootBox on %s"), *GetName());
			continue;
		}

		Inventory->AddItem(Item, ItemCount);
		CurrentLootBox->RemoveItem(Item, ItemCount);

		// Update UI grids
		LoadPlayerInventoryUIContents();
		LoadLootBoxInventoryUIContents(CurrentLootBox);
	}

	SetTakeAllButtonIsActive(false);
}

void UTradingInventoryWidget::SetTakeAllButtonIsActive_Implementation(bool IsActive)
{
	// Implemented in blueprints
}

void UTradingInventoryWidget::OnInventorySlotDoubleClicked(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot)
{
	if (!IsValid(InventorySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnInventorySlotDoubleClicked: Invalid InventorySlot"));
		return;
	}
	UDA_Item* Item = InventorySlot->GetItem();

	if (!IsValid(Item))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnInventorySlotDoubleClicked: Invalid Item on InventorySlot"));
		return;
	}
	if (!IsValid(InventoryBlockWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnInventorySlotDoubleClicked: Invalid InventoryBlockWidget"));
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
	} 
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnInventorySlotDoubleClicked: InventoryBlockWidget doesn't match either inventory block")); 
		return;
	}
}

void UTradingInventoryWidget::OnPlayerInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	if (!IsValid(InventorySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnPlayerInventorySlotDoubleClicked: Invalid InventorySlot"));
		return;
	}

	int NumItems = InventorySlot->GetNumItems();
	UDA_Item* Item = InventorySlot->GetItem();

	if (!IsValid(Item))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnPlayerInventorySlotDoubleClicked: Invalid Item in InventorySlot"));
		return;
	}
	if (!IsValid(CurrentLootBox))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnPlayerInventorySlotDoubleClicked: Invalid CurrentLootBox"));
		return;
	}
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnPlayerInventorySlotDoubleClicked: Invalid Inventory"));
		return;
	}

	CurrentLootBox->AddItem(Item, NumItems);
	Inventory->RemoveItem(Item, NumItems);

	// Update UI grids
	LoadPlayerInventoryUIContents();
	LoadLootBoxInventoryUIContents(CurrentLootBox);

	SetTakeAllButtonIsActive(true);
}

void UTradingInventoryWidget::OnLootBoxInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	if (!IsValid(InventorySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnLootBoxInventorySlotDoubleClicked: Invalid InventorySlot"));
		return;
	}
	int NumItems = InventorySlot->GetNumItems();
	UDA_Item* Item = InventorySlot->GetItem();

	if (!IsValid(Item))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnLootBoxInventorySlotDoubleClicked: Invalid Item in InventorySlot"));
		return;
	}
	if (!IsValid(CurrentLootBox))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnLootBoxInventorySlotDoubleClicked: Invalid CurrentLootBox"));
		return;
	}
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Error, TEXT("UTradingInventoryWidget::OnLootBoxInventorySlotDoubleClicked: Invalid Inventory"));
		return;
	}

	Inventory->AddItem(Item, NumItems);
	CurrentLootBox->RemoveItem(Item, NumItems);

	// Update UI grids
	LoadPlayerInventoryUIContents();
	LoadLootBoxInventoryUIContents(CurrentLootBox);

	if (CurrentLootBox->GetItemRefArray().Num() == 0)
	{
		SetTakeAllButtonIsActive(false);
	}
}