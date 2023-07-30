// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "InventoryPlayerBlockWidget.h"
#include "Inventory.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Get player pawn
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		// Get inventory component
		Inventory = Cast<UInventory>(PlayerPawn->GetComponentByClass(UInventory::StaticClass()));

		if (!Inventory) { UE_LOG(LogTemp, Error, TEXT("Cannot find Inventory in InventoryWidget, NativeConstruct")); }
	}
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
		WBP_InventoryPlayerBlock->LoadInventoryGridContents(Inventory->GetItemRefArray(), Inventory->GetItemCountArray(), Inventory->GetMaxInventorySize());

	} else { UE_LOG(LogTemp, Warning, TEXT("Cannot find WBP_InventoryPlayerBlock in InventoryWidget, UpdateInventoryUIContents")) }
}


