// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPlayerBlockWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventorySlotClicked, UInventoryPlayerBlockWidget*, InventoryBlockWidget, UWBP_InventorySlot*, InventorySlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventorySlotDoubleClicked, UInventoryPlayerBlockWidget*, InventoryBlockWidget, UWBP_InventorySlot*, InventorySlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventorySlotHovered, UInventoryPlayerBlockWidget*, InventoryBlockWidget, UWBP_InventorySlot*, InventorySlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventorySlotUnhovered, UInventoryPlayerBlockWidget*, InventoryBlockWidget, UWBP_InventorySlot*, InventorySlot);

class UUniformGridPanel;
class UDA_Item;
class UUIManager;

UCLASS()
class ODYSSEY_API UInventoryPlayerBlockWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadInventoryGridContents(TArray<UDA_Item*> ItemRefArray, TArray<int> ItemCountArray);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToGrid(UDA_Item* ItemToAdd, int ItemCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemFromGrid(UDA_Item* ItemToAdd, int ItemCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUniformGridPanel* GetInventoryGrid() { return InventoryGrid; }

public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotClicked OnInventorySlotClickedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotDoubleClicked OnInventorySlotDoubleClickedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotHovered OnInventorySlotHoveredDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotHovered OnInventorySlotUnhoveredDelegate;

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UUniformGridPanel* InventoryGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int NumInventoryCols = 6;


private:
	UFUNCTION()
	void OnInventorySlotClicked(UWBP_InventorySlot* InventorySlot);

	UFUNCTION()
	void OnInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot);

	UFUNCTION()
	void OnInventorySlotHovered(UWBP_InventorySlot* InventorySlot);

	UFUNCTION()
	void OnInventorySlotUnhhovered(UWBP_InventorySlot* InventorySlot);

private:
	UUIManager* UIManager;

};
