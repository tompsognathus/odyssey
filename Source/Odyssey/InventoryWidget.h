// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ItemDescriptionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* ItemImg;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UInventoryPlayerBlockWidget* WBP_InventoryPlayerBlock;

	/* FUNCTIONS */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemNameText(FText NewItemNameText);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemDescriptionText(FText NewItemDescriptionText);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemImg(UTexture2D* NewItemImg);


public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateInventoryUIContents();

};
