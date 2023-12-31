// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericPlatform/GenericPlatformMisc.h"

#include "WBP_AttackBtn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionBtnClickedSignature, UWBP_AttackBtn*, AttackBtn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionBtnHoveredSignature, UWBP_AttackBtn*, AttackBtn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionBtnUnhoveredSignature, UWBP_AttackBtn*, AttackBtn);

class UTextBlock;
class UButton;
class UBorder;
class UMenuAnchor;
class UCombatActionTooltipWidget;

UCLASS()
class ODYSSEY_API UWBP_AttackBtn : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AttackBtn")
	void SetActionButtonText(FText Text);

	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	FText GetActionName() const { return ActionName; }


public:
	FOnActionBtnClickedSignature OnActionButtonClickedDelegate;
	FOnActionBtnClickedSignature OnActionButtonHoveredDelegate;
	FOnActionBtnClickedSignature OnActionButtonUnhoveredDelegate;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ActionBtnText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ActionBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMenuAnchor* TooltipMenuAnchor;
	
protected:
	virtual void NativeConstruct() override;


private:
	UFUNCTION()
	void OnActionBtnClicked();

	UFUNCTION()
	void OnActionBtnHovered();

	UFUNCTION()
	void OnActionBtnUnhovered();

	UFUNCTION()
	UUserWidget* GetUserMenuContent();

	void UpdateTooltipWidgetContent();

private:
	FText ActionName;
	UCombatActionTooltipWidget* ActionTooltipWidget;
};
