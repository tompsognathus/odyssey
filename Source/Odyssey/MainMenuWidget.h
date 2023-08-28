// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UUIManager;

UCLASS()
class ODYSSEY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

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


private:
	UUIManager* UIManager;

};
