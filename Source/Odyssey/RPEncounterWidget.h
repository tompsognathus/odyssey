// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPEncounterWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API URPEncounterWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class UUIManager* UIManager;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
		void HandleOption1BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
		void HandleOption2BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
		void HandleOption3BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
		void HandleOption4BtnClicked();
};
