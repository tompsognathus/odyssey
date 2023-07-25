// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPlayerBlockWidget.generated.h"



UCLASS()
class ODYSSEY_API UInventoryPlayerBlockWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UUniformGridPanel* InventoryGrid;


	/* VARIABLES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int NumInventoryCols = 6;

public:

	void PopulateGridWithSlots();

	void FillGridWithContentsFromInventory();


private:
	class UUIManager* UIManager;
	class UInventory* Inventory;

	int NumInventorySlots;

	UFUNCTION()
	void OnInventorySlotDoubleClicked(UDA_Item* Item, int StackSize);

	UFUNCTION()
	void OnInventoryUpdated();
};
