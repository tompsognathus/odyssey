// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatWidget.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API UCombatWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* EnemyAvatar;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* EnemyNameTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CurrentRoundTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* EnemyHpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* PlayerHpBar;


	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void HandleAttack1BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void HandleAttack2BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void HandleAttack3BtnClicked();

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void HandleAttack4BtnClicked();

public:
	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyAvatar(class UMaterial* AvatarMaterial);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyName(FText EnemyName);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetCurrentRoundText(int CurrentRound);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyHpBarPercent(float Percent);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetPlayerHpBarPercent(float Percent);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat UI Functions")
	void SetActionBtnsEnabled(bool IsEnabled);
};
