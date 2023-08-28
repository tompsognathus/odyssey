// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ItemNames.h"

#include "WBP_InventorySlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoubleClicked, UWBP_InventorySlot*, InventorySlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHovered, UWBP_InventorySlot*, InventorySlot);

class UDA_Item;
class UImage;
class UTextBlock;
class UButton;
class USizeBox;

UCLASS()
class ODYSSEY_API UWBP_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItem(UDA_Item* NewItem, int NewItemCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UDA_Item* GetItem() { return Item; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetNumItems() { return StackSize; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetStackSize(int NewStackSize);

	int GetWidth();

public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnDoubleClicked OnDoubleClicked;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnHovered OnHovered;


protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DispatchOnDoubleClicked();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DispatchOnHovered();

protected:
	EItemNames ItemName = EItemNames::VE_None;

	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ItemImg;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* StackSizeText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* SizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* EmptySlotTexture;

	UPROPERTY()
	UDA_Item* Item;

	UPROPERTY()
	int StackSize;



private:
	void SetItemImg(UTexture2D* NewItemImg);

	void SetStackSizeText(FText NewStackSizeText);

	void SetItemName(EItemNames NewItemName);

private:
	class UTexture2D* EmptySlotImg;
};
