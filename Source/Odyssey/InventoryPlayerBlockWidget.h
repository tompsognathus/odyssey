// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPlayerBlockWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventorySlotDoubleClicked, UWBP_InventorySlot*, InventorySlot);

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
	void LoadInventoryGridContents();

	void AddInventorySlotToGrid(int idx);

	int AddSlotContentsToInventoryGrid(UWBP_InventorySlot* InventorySlot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveSlotContents(UWBP_InventorySlot* InventorySlot);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotDoubleClicked OnInventorySlotDoubleClickedDelegate;

private:
	class UUIManager* UIManager;
	class UInventory* Inventory;

	int NumInventorySlots = 0;

	void PopulateGridSlotsWithItems(TArray<class UDA_Item*>& InventoryItemRefs, FJsonSerializableArrayInt& InventoryItemStackSizes, int NumSlotsNeeded);

	UFUNCTION()
	void OnInventorySlotDoubleClicked(UWBP_InventorySlot* InventorySlot);


};
