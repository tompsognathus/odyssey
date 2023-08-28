// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_InventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "DA_Item.h"

void UWBP_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWBP_InventorySlot::SetItemImg(UTexture2D* NewItemImg)
{
	if (!IsValid(NewItemImg))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_InventorySlot::SetItemImg: Invalid NewItemImg"));
		return;
	}
	if (!IsValid(ItemImg))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_InventorySlot::SetItemImg: Invalid ItemImg"));
		return;
	}

	ItemImg->SetBrushFromTexture(NewItemImg);
}

void UWBP_InventorySlot::SetStackSizeText(FText NewStackSizeText)
{
	if (!IsValid(StackSizeText))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_InventorySlot::SetStackSizeText: Invalid StackSizeText"));
		return;
	}
	if (NewStackSizeText.IsEmptyOrWhitespace())
	{
		UE_LOG(LogTemp, Warning, TEXT("UWBP_InventorySlot::SetStackSizeText: NewStackSizeText is empty or whitespace"));
	}

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
		SetStackSize(NewItemCount);
		SetItemName(Item->Name);
	}
	else
	{
		SetItemImg(EmptySlotTexture);
		SetStackSize(0);
		SetItemName(EItemNames::VE_None);
	}
}

void UWBP_InventorySlot::SetStackSize(int NewStackSize)
{
	StackSize = NewStackSize;

	if (StackSize > 0)
	{
		SetStackSizeText(FText::FromString(FString::FromInt(StackSize)));
	}	
	else
	{
		SetStackSizeText(FText::FromString(""));
	}
}

int UWBP_InventorySlot::GetWidth()
{
	if (!IsValid(SizeBox))
	{
		UE_LOG(LogTemp, Error, TEXT("UWBP_InventorySlot::GetWidth: Invalid SizeBox"));
		return 0;
	}

	return SizeBox->GetWidthOverride();
}

void UWBP_InventorySlot::DispatchOnDoubleClicked()
{
	OnDoubleClicked.Broadcast(this);

}

void UWBP_InventorySlot::DispatchOnHovered()
{
	OnHovered.Broadcast(this);
}