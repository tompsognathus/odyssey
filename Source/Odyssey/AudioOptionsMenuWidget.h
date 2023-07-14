// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AudioOptionsMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UAudioOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	class UUIManager* UIManager;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleBackBtnClicked();
};
