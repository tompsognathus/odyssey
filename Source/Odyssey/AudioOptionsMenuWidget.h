// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AudioOptionsMenuWidget.generated.h"

class UUIManager;

/**
 * 
 */
UCLASS()
class ODYSSEY_API UAudioOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "UI Functions")
	void HandleBackBtnClicked();

private:
	UUIManager* UIManager;

};
