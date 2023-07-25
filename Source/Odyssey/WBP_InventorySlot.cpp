// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_InventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "DA_Item.h"

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

void UWBP_InventorySlot::SetItemName(EItemNames NewItemName)
{
	ItemName = NewItemName;
}

void UWBP_InventorySlot::SetItem(UDA_Item* NewItem, int NewItemCount)
{
	Item = NewItem;

	if (Item)
	{
		SetItemImg(Item->Icon);
		SetStackSizeText(FText::FromString(FString::FromInt(NewItemCount)));
		SetItemName(Item->Name);
	}
	else
	{
		SetItemImg(nullptr);
		SetStackSizeText(FText::FromString(""));
		SetItemName(EItemNames::VE_None);
	}
}

void UWBP_InventorySlot::SetSlotIsEnabled(bool bNewIsEnabled)
{
	Btn->SetIsEnabled(bNewIsEnabled);
}

void UWBP_InventorySlot::DispatchOnDoubleClicked()
{
	OnDoubleClicked.Broadcast(Item, StackSize);
}