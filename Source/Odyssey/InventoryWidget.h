// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UTextBlock;
class UImage;
class USizeBox;
class UInventoryPlayerBlockWidget;

UCLASS()
class ODYSSEY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void LoadInventoryUIContents();

	UFUNCTION()
	void OnInventorySlotHovered(UInventoryPlayerBlockWidget* InventoryBlockWidget, UWBP_InventorySlot* InventorySlot);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int NumInventoryCols = 6;


protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetWidthForInventoryGrid();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemNameText(FText NewItemNameText);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemDescriptionText(FText NewItemDescriptionText);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemImg(UTexture2D* NewItemImg);

protected:

	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemDescriptionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ItemImg;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UInventoryPlayerBlockWidget* WBP_InventoryPlayerBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* PlayerInventorySizeBox;


private:
	class UInventory* Inventory;
	class UUIManager* UIManager;

};
