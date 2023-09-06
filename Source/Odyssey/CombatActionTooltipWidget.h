// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatActionTooltipWidget.generated.h"

class UTextBlock;

UCLASS()
class ODYSSEY_API UCombatActionTooltipWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Combat Action Tooltip")
	void SetCombatActionName(FText NewActionName);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ActionName;
};
