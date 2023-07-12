// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UWBP_PauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class UUIManager* UIManager;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleContinueGameBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleNewGameBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOptionsBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleQuitGameBtnClicked();

};
