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

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UUniformGridPanel* PlayerActionGrid;

	//UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	//void HandleAttack1BtnClicked();

	//UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	//void HandleAttack2BtnClicked();

	//UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	//void HandleAttack3BtnClicked();

	//UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	//void HandleAttack4BtnClicked();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat UI")
	TSubclassOf<class UUserWidget> AttackBtnAssetRef;

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

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetUpAttackBtns(TArray<class UDA_ItemAction*> AttackActions);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat UI Functions")
	void SetActionBtnsEnabled(bool IsEnabled);


private:
	class UCharSheet* CharSheet;
	TArray<class UWBP_AttackBtn*> AttackBtns;

	UFUNCTION()
	void HandleAttackBtnClicked(UWBP_AttackBtn* AttackBtn);
};
