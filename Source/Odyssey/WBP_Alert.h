// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_Alert.generated.h"

class UUIManager;

UCLASS()
class ODYSSEY_API UWBP_Alert : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	/***** Quit Game *****/
	UFUNCTION(BlueprintCallable, Category = "Alert Functions")
	void HandleQuitGameYesBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "Alert Functions")
	void HandleQuitGameNoBtnClicked();

	/***** New Game *****/
	UFUNCTION(BlueprintCallable, Category = "Alert Functions")
	void HandleNewGameYesBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "Alert Functions")
	void HandleNewGameNoBtnClicked();


private:
	UUIManager* UIManager;

};
