// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "InventoryPlayerBlockWidget.h"
#include "UIManager.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
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
		WBP_InventoryPlayerBlock->PopulateGridWithSlots();

	} else { UE_LOG(LogTemp, Warning, TEXT("Cannot find WBP_InventoryPlayerBlock in InventoryWidget, UpdateInventoryUIContents")) }
}


