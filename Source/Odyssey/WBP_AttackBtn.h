// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_AttackBtn.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UWBP_AttackBtn : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ActionBtnText;

	UFUNCTION(BlueprintCallable, Category = "AttackBtn")
	void SetActionBtnText(FText Text);

};
