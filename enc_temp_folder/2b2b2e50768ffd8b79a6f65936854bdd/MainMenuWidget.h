// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FContinueGameBtnClickedSignature);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewGameBtnClickedSignature);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOptionsBtnClickedSignature);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuitGameBtnClickedSignature);

/**
 * 
 */
UCLASS()
class ODYSSEY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class UUIManager* UIManager;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleContinueGameBtnClicked();
	
	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleNewGameBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleOptionsBtnClicked();

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleQuitGameBtnClicked();



};
