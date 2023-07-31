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

	void SetWidthForInventoryGrids();
	
	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UInventoryPlayerBlockWidget* WBP_InventoryLootBoxBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UInventoryPlayerBlockWidget* WBP_InventoryPlayerBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USizeBox* PlayerInventorySizeBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USizeBox* LootInventorySizeBox;

	/* VARIABLES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int NumInventoryCols = 5;

private:
	class UUIManager* UIManager;
	class UInventory* Inventory;

	class ULootBox* CurrentLootBox;

	UFUNCTION()
	void OnInventorySlotDoubleClicked(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot);

	void OnPlayerInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot);

	void OnLootBoxInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot);


public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadPlayerInventoryUIContents();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadLootBoxInventoryUIContents(class ULootBox* LootBox);
};
