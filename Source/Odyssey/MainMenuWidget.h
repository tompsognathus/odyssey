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
	void HandleContinueGameButtonClicked();
	
	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleNewGameButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOptionsButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleQuitGameButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleCreditsButtonClicked();


private:
	UUIManager* UIManager;

};
