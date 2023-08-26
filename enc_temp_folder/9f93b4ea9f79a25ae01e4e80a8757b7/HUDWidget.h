// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* GpText;

private:
	class UCharSheet* CharSheet;
	class AOdysseyCharacter* Player;

	UFUNCTION()
	void SetHpBar(float Percent);
	
	UFUNCTION()
	void SetGpText(int32 Gp);

};
