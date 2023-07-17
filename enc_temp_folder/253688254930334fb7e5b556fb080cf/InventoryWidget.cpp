// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"

#include "UIManager.h"
#include "Inventory.h"

void UInventoryWidget::NativeConstruct()
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

	// Populate grid with inventory slot widgets
	int InventorySize = Inventory->GetInventorySize();
	for (int idx = 0; idx < InventorySize; idx++)
	{
		UUserWidget* InventorySlotWidget = CreateWidget<UUserWidget>(GetWorld(), UIManager->InventorySlotAssetRef);
		// Add to grid
		InventoryGrid->AddChildToUniformGrid(InventorySlotWidget, idx / 4, idx % 4);
	}
}

void UInventoryWidget::SetItemNameText(FText NewItemNameText)
{
	ItemNameText->SetText(NewItemNameText);
}

void UInventoryWidget::SetItemDescriptionText(FText NewItemDescriptionText)
{
	ItemDescriptionText->SetText(NewItemDescriptionText);
}

void UInventoryWidget::SetItemImg(UTexture2D* NewItemImg)
{
	ItemImg->SetBrushFromTexture(NewItemImg);
}

void UInventoryWidget::DisplayItem(int ItemIdx)
{

}