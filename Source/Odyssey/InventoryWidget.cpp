// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "InventoryPlayerBlockWidget.h"
#include "Inventory.h"
#include "UIManager.h"
#include "WBP_InventorySlot.h"
#include "DA_Item.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

	SetWidthForInventoryGrid();

	// Bind delegates
	if (WBP_InventoryPlayerBlock)
	{
		WBP_InventoryPlayerBlock->OnInventorySlotHoveredDelegate.AddDynamic(this, &UInventoryWidget::OnInventorySlotHovered);

	}
	else { UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryPlayerBlock in InventoryWidget, NativeConstruct")); }
}


void UInventoryWidget::SetWidthForInventoryGrid()
{
	int InventorySlotWidth = 100;
	// Create an empty slot widget to get its size
	UWBP_InventorySlot* EmptySlot = CreateWidget<UWBP_InventorySlot>(this, UIManager->InventorySlotAssetRef);
	if (EmptySlot)
	{
		InventorySlotWidth = EmptySlot->GetWidth();

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find InventorySlotAssetRef in TradingInventoryWidget, NativeConstruct")); }

	int GridWidth = NumInventoryCols * InventorySlotWidth;
	// Set the width override for both grids based on the number of columns and the size of the slots
	if (PlayerInventorySizeBox)
	{
		PlayerInventorySizeBox->SetWidthOverride(GridWidth);

	} else { UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerInventorySizeBox in TradingInventoryWidget, NativeConstruct")); }

}

void UInventoryWidget::SetItemNameText(FText NewItemNameText)
{
	if (ItemNameText)
	{
		ItemNameText->SetText(NewItemNameText);

	} else { UE_LOG(LogTemp, Warning, TEXT("Cannot find ItemNameText in InventoryWidget, SetItemNameText")) }
}

void UInventoryWidget::SetItemDescriptionText(FText NewItemDescriptionText)
{
	if (ItemDescriptionText)
	{
		ItemDescriptionText->SetText(NewItemDescriptionText);

	} else { UE_LOG(LogTemp, Warning, TEXT("Cannot find ItemDescriptionText in InventoryWidget, SetItemDescriptionText")) }
}

void UInventoryWidget::SetItemImg(UTexture2D* NewItemImg)
{
	if (ItemImg)
	{
		ItemImg->SetBrushFromTexture(NewItemImg);

	} else { UE_LOG(LogTemp, Warning, TEXT("Cannot find ItemImg in InventoryWidget, SetItemImg")) }
}

void UInventoryWidget::LoadInventoryUIContents()
{
	if (WBP_InventoryPlayerBlock)
	{
		WBP_InventoryPlayerBlock->LoadInventoryGridContents(Inventory->GetItemRefArray(), Inventory->GetItemCountArray());

	} else { UE_LOG(LogTemp, Warning, TEXT("Cannot find WBP_InventoryPlayerBlock in InventoryWidget, UpdateInventoryUIContents")) }
}

void UInventoryWidget::OnInventorySlotHovered(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot)
{
	UE_LOG(LogTemp, Warning, TEXT("Hovered over inventory slot"));

	SetItemNameText(FText::FromString(InventorySlot->GetItem()->DisplayName));
	SetItemDescriptionText(FText::FromString(InventorySlot->GetItem()->Description));
	SetItemImg(InventorySlot->GetItem()->Icon);
}

