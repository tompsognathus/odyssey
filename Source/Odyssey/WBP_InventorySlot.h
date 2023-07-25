// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ItemNames.h"

#include "WBP_InventorySlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDoubleClicked, UDA_Item*, Item, int, StackSize);

UCLASS()
class ODYSSEY_API UWBP_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	EItemNames ItemName = EItemNames::VE_None;

	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* ItemImg;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StackSizeText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Btn;

	UPROPERTY()
	class UDA_Item* Item;

	UPROPERTY()
	int StackSize;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DispatchOnDoubleClicked();


public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnDoubleClicked OnDoubleClicked;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItem(class UDA_Item* NewItem, int NewItemCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UDA_Item* GetItem() { return Item; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSlotIsEnabled(bool bNewIsEnabled);


private:
	void SetItemImg(UTexture2D* NewItemImg);

	void SetStackSizeText(FText NewStackSizeText);

	void SetItemName(EItemNames NewItemName);
};
