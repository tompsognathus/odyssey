// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_InventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UWBP_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWBP_InventorySlot::SetItemImg(UTexture2D* NewItemImg)
{
	ItemImg->SetBrushFromTexture(NewItemImg);
}

void UWBP_InventorySlot::SetStackSizeText(FText NewStackSizeText)
{
	StackSizeText->SetText(NewStackSizeText);
}
