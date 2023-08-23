// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericPlatform/GenericPlatformMisc.h"

#include "WBP_AttackBtn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionBtnClickedSignature, UWBP_AttackBtn*, AttackBtn);
/**
 * 
 */
UCLASS()
class ODYSSEY_API UWBP_AttackBtn : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnActionBtnClickedSignature OnActionBtnClickedDelegate;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ActionBtnText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ActionBtn;

	UFUNCTION(BlueprintCallable, Category = "AttackBtn")
	void SetActionBtnText(FText Text);

private:
	UFUNCTION()
	void OnActionBtnClicked();
};
