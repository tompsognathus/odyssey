// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPlayerBlockWidget.h"
#include "Inventory.h"
#include "UIManager.h"
#include "Components/UniformGridPanel.h"


void UInventoryPlayerBlockWidget::NativeConstruct()
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
		InventoryGrid->AddChildToUniformGrid(InventorySlotWidget, idx / NumInventoryCols, idx % NumInventoryCols);
	}
}
