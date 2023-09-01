// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MemoryCardWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UMemoryCardWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void CallOnMemoryCardClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void CallOnMemoryCardHovered();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void CallOnMemoryCardUnHovered();


};
