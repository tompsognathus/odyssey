// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatActionRequested, UDA_ItemAction*, ItemAction);

class UImage;
class UTextBlock;
class UProgressBar;
class UUniformGridPanel;
class UUserWidget;
class UMaterial;
class UDA_ItemAction;
class UWBP_AttackBtn;
class UBorder;

UCLASS()
class ODYSSEY_API UCombatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyAvatar(UMaterial* AvatarMaterial);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyName(FText& EnemyName);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetCurrentRoundText(int CurrentRound);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetEnemyHpBarPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetPlayerHpBarPercent(float NormalizedPercent);

	UFUNCTION(BlueprintCallable, Category = "Combat UI Functions")
	void SetUpAttackButtons(TArray<UDA_ItemAction*> AttackActions);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat UI Functions")
	void SetActionBtnsEnabled(bool IsEnabled);

	void SetUpCombatantBindings(class UCharSheet* PlayerCharSheet, class UCharSheet* EnemyCharSheet);

	void RemoveCombatantBindings();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat UI")
	TSubclassOf<UUserWidget> AttackButtonAssetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat UI")
	int NumButtonsPerRow = 4;

	FOnCombatActionRequested OnCombatActionRequestedDelegate;


protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* EnemyAvatar;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* EnemyNameTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CurrentRoundTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* EnemyHpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* PlayerHpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UUniformGridPanel* PlayerActionGrid;

	/* Featured attack pop-up */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UBorder* AttackDetailsPopup;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* FeaturedAttackName;

private:
	UFUNCTION()
	void HandleAttackButtonClicked(UWBP_AttackBtn* AttackBtn);

	UFUNCTION()
	void HandleAttackButtonHovered(UWBP_AttackBtn* AttackBtn);

	UFUNCTION()
	void HandleAttackButtonUnhovered(UWBP_AttackBtn* AttackBtn);

	UFUNCTION()
	void HandleCombatActionRequested(UDA_ItemAction* ItemAction);

private:
	class UCharSheet* PlayerCharSheet;
	class UCharSheet* EnemyCharSheet;

	TArray<UWBP_AttackBtn*> AttackButtons = TArray<UWBP_AttackBtn*>();
	TArray<UDA_ItemAction*> AttackActions = TArray<UDA_ItemAction*>();
	
};
