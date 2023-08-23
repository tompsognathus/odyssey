// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatActionRequested, UDA_ItemAction*, ItemAction);
/**
 * 
 */
UCLASS()
class ODYSSEY_API UCombatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnCombatActionRequested OnCombatActionRequestedDelegate;

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
	void SetEnemyHpBarPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetPlayerHpBarPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetUpAttackBtns(TArray<class UDA_ItemAction*> AttackActions);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat UI Functions")
	void SetActionBtnsEnabled(bool IsEnabled);

	void SetUpCombatantBindings(class UCharSheet* PlayerCharSheet, class UCharSheet* EnemyCharSheet);

	void RemoveCombatantBindings();

private:
	class UCharSheet* PlayerCharSheet;
	class UCharSheet* EnemyCharSheet;

	TArray<class UWBP_AttackBtn*> AttackBtns;
	TArray<class UDA_ItemAction*> AttackActions;

	UFUNCTION()
	void HandleAttackBtnClicked(UWBP_AttackBtn* AttackBtn);

	UFUNCTION()
	void HandleCombatActionRequested(class UDA_ItemAction* ItemAction);
	
};
