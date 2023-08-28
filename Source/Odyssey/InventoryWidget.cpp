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
#include "Utility.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIManager = Utility::GetUIManager(this);
	if (!IsValid(UIManager)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::NativeConstruct: Invalid UIManager")); 
		return;
	}
	
	Inventory = Utility::GetInventory(this);
	if (!IsValid(Inventory)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::NativeConstruct: Invalid Inventory")); 
		return;
	}

	SetWidthForInventoryGrid();

	// Bind delegates
	if (!IsValid(WBP_InventoryPlayerBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::NativeConstruct: Invalid WBP_InventoryPlayerBlock"));
		return;
	}
	WBP_InventoryPlayerBlock->OnInventorySlotHoveredDelegate.AddDynamic(this, &UInventoryWidget::OnInventorySlotHovered);
}


void UInventoryWidget::SetWidthForInventoryGrid()
{
	int InventorySlotWidth = 100;

	// Create an empty slot widget to get its size
	if (!IsValid(UIManager))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::SetWidthForInventoryGrid: Invalid UIManager"));
		return;
	}

	TSubclassOf<class UUserWidget> InventorySlotAssetRef = UIManager->InventorySlotAssetRef;
	if (!IsValid(InventorySlotAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::SetWidthForInventoryGrid: Invalid InventorySlotAssetRef"));
		return;
	}

	UWBP_InventorySlot* EmptySlot = CreateWidget<UWBP_InventorySlot>(this, InventorySlotAssetRef);
	if (!IsValid(EmptySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::SetWidthForInventoryGrid: Invalid EmptySlot"));
		return;
	}

	InventorySlotWidth = EmptySlot->GetWidth();
	int GridWidth = NumInventoryCols * InventorySlotWidth;

	// Set the width override for both grids based on the number of columns and the size of the slots
	if (!IsValid(PlayerInventorySizeBox))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::SetWidthForInventoryGrid: Invalid PlayerInventorySizeBox"));
		return;
	}
	PlayerInventorySizeBox->SetWidthOverride(GridWidth);
}

void UInventoryWidget::SetItemNameText(FText NewItemNameText)
{
	if (!IsValid(ItemNameText))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget::SetItemNameText: Invalid ItemNameText"));
		return;
	}
	if (NewItemNameText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget::SetItemNameText: NewItemNameText is empty or whitespace"));
		return;
	}

	ItemNameText->SetText(NewItemNameText);
}

void UInventoryWidget::SetItemDescriptionText(FText NewItemDescriptionText)
{
	if (!IsValid(ItemDescriptionText))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::SetItemDescriptionText: Invalid ItemDescriptionText"));
		return;
	}
	if (NewItemDescriptionText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::SetItemDescriptionText: NewItemDescriptionText is empty or whitespace"));
		return;
	}

	ItemDescriptionText->SetText(NewItemDescriptionText);
}

void UInventoryWidget::SetItemImg(UTexture2D* NewItemImg)
{
	if (!IsValid(ItemImg))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::SetItemImg: Invalid ItemImg"));
		return;
	}
	if (!IsValid(NewItemImg))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::SetItemImg: Invalid NewItemImg"));
		return;
	}

	ItemImg->SetBrushFromTexture(NewItemImg);
}

void UInventoryWidget::LoadInventoryUIContents()
{
	if (!IsValid(WBP_InventoryPlayerBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::LoadInventoryUIContents: Invalid WBP_InventoryPlayerBlock"));
		return;
	}
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::LoadInventoryUIContents: Invalid Inventory"));
		return;
	}

	WBP_InventoryPlayerBlock->LoadInventoryGridContents(Inventory->GetItemRefArray(), Inventory->GetItemCountArray());
}

void UInventoryWidget::OnInventorySlotHovered(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot)
{
	if (!IsValid(InventorySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::OnInventorySlotHovered: InvalidInventorySlot"));
		return;
	}
	if (!IsValid(InventoryBlockWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::OnInventorySlotHovered: Invalid InventoryBlockWidget"));
		return;
	}

	FText HoveredItemDisplayNameText = FText::FromString(InventorySlot->GetItem()->DisplayName);
	if (HoveredItemDisplayNameText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::OnInventorySlotHovered: ItemDisplayNameText is empty or whitespace"));
		return;
	}
	SetItemNameText(HoveredItemDisplayNameText);

	FText HoveredItemDescriptionText = FText::FromString(InventorySlot->GetItem()->Description);
	if (HoveredItemDescriptionText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::OnInventorySlotHovered: ItemDescriptionText is empty or whitespace"));
		return;
	}
	SetItemDescriptionText(HoveredItemDescriptionText);

	UTexture2D* HoveredItemImgTexture = InventorySlot->GetItem()->Icon;
	if (!IsValid(HoveredItemImgTexture))
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryWidget::OnInventorySlotHovered: Invalid ItemImgTexture"));
		return;
	}
	SetItemImg(HoveredItemImgTexture);
}

