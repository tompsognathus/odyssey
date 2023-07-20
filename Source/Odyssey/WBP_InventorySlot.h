// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UWBP_InventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
	/* WIDGET BINDINGS */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* ItemImg;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* StackSizeText;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemImg(UTexture2D* NewItemImg);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetStackSizeText(FText NewStackSizeText);

};
