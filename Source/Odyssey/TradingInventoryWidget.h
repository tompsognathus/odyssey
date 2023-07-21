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

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdatePlayerInventoryUIContents();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateAvailableLootUIContents(class ULootBox* LootBox);

};
