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
	Super::NativeConstruct();
	
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid World in InventoryWidget, NativeConstruct"));
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid PlayerController in InventoryWidget, NativeConstruct"));
		return;
	}

	APawn* PlayerPawn = PlayerController->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid PlayerPawn in InventoryWidget, NativeConstruct"));
		return;
	}

	UActorComponent* UIManagerComponent = PlayerPawn->GetComponentByClass(UUIManager::StaticClass());
	if (!UIManagerComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManagerComponent in InventoryWidget, NativeConstruct"));
		return;
	}

	UIManager = Cast<UUIManager>(UIManagerComponent);
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot cast UIManagerComponent to UUIManager in InventoryWidget, NativeConstruct"));
		return;
	}

}

void UInventoryPlayerBlockWidget::LoadInventoryGridContents(TArray<class UDA_Item*> ItemRefArray, TArray<int> ItemCountArray)
{
	InventoryGrid->ClearChildren();

	int NumSlots = ItemRefArray.Num();
	UDA_Item* ItemToAdd = nullptr;
	int ItemCount = 0;

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
	if (!IsValid(ItemToAdd))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid ItemToAdd in InventoryWidget, AddItemToGrid"));
		return;
	}
	if (!IsValid(InventoryGrid))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid InventoryGrid in InventoryWidget, AddItemToGrid"));
		return;
	}

	UWBP_InventorySlot* InventorySlot = nullptr;

	// If the item already exists in the grid, find it and add to the count
	for (int idx = 0; idx < InventoryGrid->GetChildrenCount(); idx++)
	{
		InventorySlot = Cast<UWBP_InventorySlot>(InventoryGrid->GetChildAt(idx));
		if (!IsValid(InventorySlot))
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid InventorySlot in InventoryWidget, AddItemToGrid"));
			return;
		}

		if (InventorySlot->GetItem()->Name == ItemToAdd->Name)
		{
			InventorySlot->SetStackSize(InventorySlot->GetNumItems() + ItemCount);
			return;
		}
	}
	// Otherwise create a new slot
	TSubclassOf<UUserWidget> InventorySlotAssetRef = UIManager->InventorySlotAssetRef;
	if (!IsValid(InventorySlotAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid InventorySlotAssetRef in InventoryWidget, AddItemToGrid. Is it assigned in the UIManager?"));
		return;
	}

	UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), InventorySlotAssetRef);
	if (!IsValid(InventorySlotWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid InventorySlotWidget in InventoryWidget, AddItemToGrid. Couldn't create it..."));
		return;
	}

	InventorySlot = Cast<UWBP_InventorySlot>(InventorySlotWidget);
	if (!IsValid(InventorySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid InventorySlot in InventoryWidget, AddItemToGrid."));
		return;
	}

	// Compute index for this new slot
	int idx = InventoryGrid->GetChildrenCount();

	int SlotRow = idx / NumInventoryCols;
	int SlotCol = idx % NumInventoryCols;
	
	// Add the slot to the grid
	InventoryGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);
	InventorySlot->SetItem(ItemToAdd, ItemCount);

	// Bind functions to On Double Clicked event in inventory slot widget
	InventorySlot->OnDoubleClicked.AddDynamic(this, &UInventoryPlayerBlockWidget::OnInventorySlotDoubleClicked);
	InventorySlot->OnHovered.AddDynamic(this, &UInventoryPlayerBlockWidget::OnInventorySlotHovered);

}

void UInventoryPlayerBlockWidget::RemoveItemFromGrid(UDA_Item* ItemToRemove, int NumToRemove)
{
	if (!IsValid(ItemToRemove))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid ItemToRemove in InventoryWidget, RemoveItemFromGrid"));
		return;
	}
	if (!IsValid(InventoryGrid))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid InventoryGrid in InventoryWidget, RemoveItemFromGrid"));
		return;
	}

	// Find slot in grid
	for (int idx = 0; idx < InventoryGrid->GetChildrenCount(); idx++)
	{
		UWidget* SlotWidget = InventoryGrid->GetChildAt(idx);
		if (!IsValid(SlotWidget))
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid SlotWidget in InventoryWidget, RemoveItemFromGrid"));
			return;
		}

		UWBP_InventorySlot* InventorySlot = Cast<UWBP_InventorySlot>(SlotWidget);
		if (!IsValid(InventorySlot))
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid InventorySlot in InventoryWidget, RemoveItemFromGrid"));
			return;
		}

		UDA_Item* ItemInSlot = InventorySlot->GetItem();
		if (!IsValid(ItemInSlot))
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid ItemInSlot in InventoryWidget, RemoveItemFromGrid"));
			return;
		}

		if (ItemInSlot == ItemToRemove)
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
	}
}

void UInventoryPlayerBlockWidget::OnInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot)
{
	if (!IsValid(InventorySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid InventorySlot in InventoryWidget, OnInventorySlotDoubleClicked"));
		return;
	}
	OnInventorySlotDoubleClickedDelegate.Broadcast(this, InventorySlot);
}

void UInventoryPlayerBlockWidget::OnInventorySlotHovered(UWBP_InventorySlot* InventorySlot)
{
	if (!IsValid(InventorySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid InventorySlot in InventoryWidget, OnInventorySlotHovered"));
		return;
	}
	OnInventorySlotHoveredDelegate.Broadcast(this, InventorySlot);
}



 