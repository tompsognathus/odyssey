// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_OptionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UWBP_OptionsMenu : public UUserWidget
{
	GENERATED_BODY()
	

private:
	class UUIManager* UIManager;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
		void HandleAudioBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
		void HandleVideoBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
		void HandleGameplayBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
		void HandleBackBtnClicked();

};
