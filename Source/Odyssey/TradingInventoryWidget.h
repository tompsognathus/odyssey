// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradingInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UTradingInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UUniformGridPanel* AvailableLootGrid;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UInventoryPlayerBlockWidget* WBP_InventoryPlayerBlock;

	/* VARIABLES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int NumInventoryCols = 5;

private:
	class UUIManager* UIManager;
	class UInventory* Inventory;

	class ULootBox* CurrentLootBox;

	int NumLootBoxSlots = 0;

	UFUNCTION()
	void OnLootableSlotDoubleClicked(UWBP_InventorySlot* InventorySlot);

	UFUNCTION()
	void OnInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot);


public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadPlayerInventoryUIContents();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadAvailableLootUIContents(class ULootBox* LootBox);

	void AddInventorySlotToGrid(int idx);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveSlotContents(UWBP_InventorySlot* InventorySlot);


};
