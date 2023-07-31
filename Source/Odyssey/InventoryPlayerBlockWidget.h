// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPlayerBlockWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventorySlotDoubleClicked, UInventoryPlayerBlockWidget*, InventoryBlockWidget, UWBP_InventorySlot*, InventorySlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventorySlotHovered, UInventoryPlayerBlockWidget*, InventoryBlockWidget, UWBP_InventorySlot*, InventorySlot);

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
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadInventoryGridContents(TArray<class UDA_Item*> ItemRefArray, TArray<int> ItemCountArray);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToGrid(UDA_Item* ItemToAdd, int ItemCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemFromGrid(UDA_Item* ItemToAdd, int ItemCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUniformGridPanel* GetInventoryGrid() { return InventoryGrid; }

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotDoubleClicked OnInventorySlotDoubleClickedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotHovered OnInventorySlotHoveredDelegate;

private:
	class UUIManager* UIManager;

	UFUNCTION()
	void OnInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot);

	UFUNCTION()
	void OnInventorySlotHovered(UWBP_InventorySlot* InventorySlot);


};
