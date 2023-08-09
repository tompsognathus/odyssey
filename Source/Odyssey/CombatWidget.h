// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UCombatWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleAttack1BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleAttack2BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleAttack3BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleAttack4BtnClicked();





};
