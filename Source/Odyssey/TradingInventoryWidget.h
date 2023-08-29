// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TradingInventoryWidget.generated.h"

class UInventoryPlayerBlockWidget;
class USizeBox;
class UUIManager;
class UInventory;
class ULootBox;

class UWBP_MenuBtn;

UCLASS()
class ODYSSEY_API UTradingInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadPlayerInventoryUIContents();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadLootBoxInventoryUIContents(ULootBox* LootBox);


protected:
	virtual void NativeConstruct() override;

	void SetWidthForInventoryGrids();
	
	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleTakeAllButtonClicked();

	UFUNCTION(BlueprintNativeEvent, Category = "UI Functions")
	void SetTakeAllButtonIsActive(bool IsActive);

protected:
	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryPlayerBlockWidget* WBP_InventoryLootBoxBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryPlayerBlockWidget* WBP_InventoryPlayerBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* PlayerInventorySizeBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* LootInventorySizeBox;

	/* VARIABLES */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int NumInventoryCols = 5;


private:
	UFUNCTION()
	void OnInventorySlotDoubleClicked(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot);

	void OnPlayerInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot);

	void OnLootBoxInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot);

private:
	UUIManager* UIManager;
	UInventory* Inventory;
	ULootBox* CurrentLootBox;
};
