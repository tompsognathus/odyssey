// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "UIManager.h"

void UInventoryWidget::NativeConstruct()
{

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


