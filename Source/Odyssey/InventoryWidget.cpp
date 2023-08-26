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

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find world in InventoryWidget, NativeConstruct"));
		return;
	}

	APlayerController* FirstPlayerController = World->GetFirstPlayerController();
	if (!IsValid(FirstPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find player controller in InventoryWidget, NativeConstruct"));
		return;
	}

	APawn* PlayerPawn = FirstPlayerController->GetPawn();
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find player pawn in InventoryWidget, NativeConstruct"));
		return;
	}

	UActorComponent* UIManagerComponent = PlayerPawn->GetComponentByClass(UUIManager::StaticClass());
	if (!IsValid(UIManagerComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManagerComponent in InventoryWidget, NativeConstruct"));
		return;
	}

	UIManager = Cast<UUIManager>(UIManagerComponent);
	if (!IsValid(UIManager)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in InventoryWidget, NativeConstruct")); 
		return;
	}

	UActorComponent* InventoryComponent = PlayerPawn->GetComponentByClass(UInventory::StaticClass());
	if (!IsValid(InventoryComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find InventoryComponent in InventoryWidget, NativeConstruct"));
		return;
	}
	
	Inventory = Cast<UInventory>(InventoryComponent);
	if (!IsValid(Inventory)) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Cannot find Inventory in InventoryWidget, NativeConstruct")); 
		return;
	}

	SetWidthForInventoryGrid();

	// Bind delegates
	if (!IsValid(WBP_InventoryPlayerBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryPlayerBlock in InventoryWidget, NativeConstruct"));
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
		UE_LOG(LogTemp, Error, TEXT("Cannot find UIManager in InventoryWidget, SetWidthForInventoryGrid"));
		return;
	}

	TSubclassOf<class UUserWidget> InventorySlotAssetRef = UIManager->InventorySlotAssetRef;
	if (!IsValid(InventorySlotAssetRef))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find InventorySlotAssetRef in InventoryWidget, SetWidthForInventoryGrid"));
		return;
	}

	UWBP_InventorySlot* EmptySlot = CreateWidget<UWBP_InventorySlot>(this, InventorySlotAssetRef);
	if (!IsValid(EmptySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot create EmptySlot in InventoryWidget, SetWidthForInventoryGrid"));
		return;
	}

	InventorySlotWidth = EmptySlot->GetWidth();
	int GridWidth = NumInventoryCols * InventorySlotWidth;

	// Set the width override for both grids based on the number of columns and the size of the slots
	if (!IsValid(PlayerInventorySizeBox))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find PlayerInventorySizeBox in InventoryWidget, SetWidthForInventoryGrid"));
		return;
	}
	PlayerInventorySizeBox->SetWidthOverride(GridWidth);
}

void UInventoryWidget::SetItemNameText(FText NewItemNameText)
{
	if (!IsValid(ItemNameText))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find ItemNameText in InventoryWidget, SetItemNameText"));
		return;
	}
	if (NewItemNameText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Warning, TEXT("NewItemNameText is empty in InventoryWidget, SetItemNameText"));
		return;
	}

	ItemNameText->SetText(NewItemNameText);
}

void UInventoryWidget::SetItemDescriptionText(FText NewItemDescriptionText)
{
	if (!IsValid(ItemDescriptionText))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find ItemDescriptionText in InventoryWidget, SetItemDescriptionText"));
		return;
	}
	if (NewItemDescriptionText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("NewItemDescriptionText is empty in InventoryWidget, SetItemDescriptionText"));
		return;
	}

	ItemDescriptionText->SetText(NewItemDescriptionText);
}

void UInventoryWidget::SetItemImg(UTexture2D* NewItemImg)
{
	if (!IsValid(ItemImg))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find ItemImg in InventoryWidget, SetItemImg"));
		return;
	}
	if (!IsValid(NewItemImg))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find NewItemImg in InventoryWidget, SetItemImg"));
		return;
	}

	ItemImg->SetBrushFromTexture(NewItemImg);
}

void UInventoryWidget::LoadInventoryUIContents()
{
	if (!IsValid(WBP_InventoryPlayerBlock))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find WBP_InventoryPlayerBlock in InventoryWidget, UpdateInventoryUIContents"));
		return;
	}
	if (!IsValid(Inventory))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find Inventory in InventoryWidget, UpdateInventoryUIContents"));
		return;
	}

	WBP_InventoryPlayerBlock->LoadInventoryGridContents(Inventory->GetItemRefArray(), Inventory->GetItemCountArray());
}

void UInventoryWidget::OnInventorySlotHovered(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot)
{
	if (!IsValid(InventorySlot))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find InventorySlot in InventoryWidget, OnInventorySlotHovered"));
		return;
	}
	if (!IsValid(InventoryBlockWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find InventoryBlockWidget in InventoryWidget, OnInventorySlotHovered"));
		return;
	}

	FText HoveredItemDisplayNameText = FText::FromString(InventorySlot->GetItem()->DisplayName);
	if (HoveredItemDisplayNameText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("ItemDisplayNameText is empty in InventoryWidget, OnInventorySlotHovered"));
		return;
	}
	SetItemNameText(HoveredItemDisplayNameText);

	FText HoveredItemDescriptionText = FText::FromString(InventorySlot->GetItem()->Description);
	if (HoveredItemDescriptionText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Error, TEXT("ItemDescriptionText is empty in InventoryWidget, OnInventorySlotHovered"));
		return;
	}
	SetItemDescriptionText(HoveredItemDescriptionText);

	UTexture2D* HoveredItemImgTexture = InventorySlot->GetItem()->Icon;
	if (!IsValid(HoveredItemImgTexture))
	{
		UE_LOG(LogTemp, Error, TEXT("ItemImgTexture is invalid in InventoryWidget, OnInventorySlotHovered."));
		return;
	}
	SetItemImg(HoveredItemImgTexture);
}

