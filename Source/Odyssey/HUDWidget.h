// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UCharSheet;
class AOdysseyCharacter;

/**
 * 
 */
UCLASS()
class ODYSSEY_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* GpText;

private:
	UFUNCTION()
	void SetHpBar(float Percent);
	
	UFUNCTION()
	void SetGpText(int32 Gp);

private:
	UCharSheet* CharSheet;
	AOdysseyCharacter* Player;

};
