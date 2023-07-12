// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_Alert.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UWBP_Alert : public UUserWidget
{
	GENERATED_BODY()
	
private:
class UUIManager* UIManager;

protected:
virtual void NativeConstruct() override;

UFUNCTION(BlueprintCallable, Category = "Alert Functions")
void HandleYesBtnClicked();

UFUNCTION(BlueprintCallable, Category = "Alert Functions")
void HandleNoBtnClicked();

};
